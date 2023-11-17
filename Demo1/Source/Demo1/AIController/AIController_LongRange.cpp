// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_LongRange.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"

AAIController_LongRange::AAIController_LongRange()
{
	M_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
	if (M_AIPerception)
	{
		M_AIPerception->ConfigureSense(*SightConfig);
		M_AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AAIController_LongRange::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAICharacter_Base* AI_LongRange = Cast<AAICharacter_Base>(InPawn);

	// 处理一下感知组件
	if (SightConfig)
	{
		// 这一块的配置直接去 AI 上面取就行
		if (AI_LongRange)
		{
			SightConfig->SightRadius = AI_LongRange->PerceptionRadius;
			SightConfig->LoseSightRadius = AI_LongRange->LosePerceptionRadius;
		}
		else
		{
			SightConfig->SightRadius = 3000;
			SightConfig->LoseSightRadius = 3500;
		}

		SightConfig->PeripheralVisionAngleDegrees = 180.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	}
	if (M_AIPerception)
	{
		M_AIPerception->ConfigureSense(*SightConfig);
	}

	if (AI_LongRange)
	{
		AI_LongRange->Init();
	}
}

void AAIController_LongRange::BeginPlay()
{
	Super::BeginPlay();

	if (M_AIPerception)
	{
		M_AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AAIController_LongRange::OnTargetPerceptionUpdated);
	}

	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

}

void AAIController_LongRange::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 更新一下状态
	UpdateState();

	// 尝试发出攻击
	TryAttack();

}

// --------------------------------------------- AI Behavior Tree ------------------------------------------------

AAICharacter_Base* AAIController_LongRange::GetLockedEnemy()
{
	return M_LockedEnemy;
}

void AAIController_LongRange::SetLockedEnemy(AAICharacter_Base* Enemy)
{
	M_LockedEnemy = Enemy;
}

// 更新一下是否进入攻击范围的状态
void AAIController_LongRange::UpdateState()
{
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	if (PossessAI == nullptr || PossessAI->IsDead()) return;

	// 目标存在，且未死亡
	if (M_LockedEnemy && !M_LockedEnemy->IsDead())
	{
		float dis = FVector::Distance(PossessAI->GetActorLocation(), M_LockedEnemy->GetActorLocation());
		if (dis <= PossessAI->AttackRadius)
		{
			if (GetBlackboard() && !GetBlackboard()->GetValueAsBool(FName("IsInAttackRange")))
			{
				GetBlackboard()->SetValueAsBool(FName("IsInAttackRange"), true);
			}
		}
		else
		{
			if (GetBlackboard() && GetBlackboard()->GetValueAsBool(FName("IsInAttackRange")))
			{
				GetBlackboard()->SetValueAsBool(FName("IsInAttackRange"), false);
			}
		}
	}
	// 不存在或者死亡，则设置一下 Target 为空，且重置攻击范围状态
	else
	{
		if (GetBlackboard() && GetBlackboard()->GetValueAsObject(FName("Target")))
		{
			GetBlackboard()->SetValueAsObject(FName("Target"), nullptr);
		}

		if (GetBlackboard() && GetBlackboard()->GetValueAsBool(FName("IsInAttackRange")))
		{
			GetBlackboard()->SetValueAsBool(FName("IsInAttackRange"), false);
		}
	}
}

// 尝试发出攻击
void AAIController_LongRange::TryAttack()
{
	AAICharacter_LongRange* PossessAI = Cast<AAICharacter_LongRange>(GetPawn());
	bool IsInAttackRange = GetBlackboard()->GetValueAsBool(FName("IsInAttackRange"));

	// 当前属于攻击范围内，且定时器句柄不在，才发起一次攻击
	if (PossessAI && IsInAttackRange && !GetWorldTimerManager().IsTimerActive(M_TimerHandle))
	{
		PossessAI->AttackEnemy();
	}
}

void AAIController_LongRange::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AAICharacter_Base* Enemy = Cast<AAICharacter_Base>(Actor);
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	// 死亡，同阵营直接跳过
	if (!Enemy || Enemy->IsDead() || !PossessAI || PossessAI->IsDead() || (Enemy->GetCampType() == PossessAI->GetCampType()))
	{
		return;
	}

	// 进入感知
	if (Stimulus.WasSuccessfullySensed())
	{
		M_Blackboard->SetValueAsBool("IsPerception", true);		// 用于打断巡逻任务

		if (!M_EnemyArray.Contains(Enemy))
		{
			M_EnemyArray.Add(Enemy);
		}
	}
	// 离开感知
	else
	{
		// 如果当前目标离开，则置空
		if (Actor == M_Blackboard->GetValueAsObject("Target"))
		{
			M_Blackboard->SetValueAsObject("Target", nullptr);
			SetLockedEnemy(nullptr);
		}

		// 如果队列里面有，则删除
		if (M_EnemyArray.Contains(Enemy))
		{
			M_EnemyArray.Remove(Enemy);
		}
	}
}

void AAIController_LongRange::FindTarget()
{
	AAICharacter_Base* Target = Cast<AAICharacter_Base>(M_Blackboard->GetValueAsObject("Target"));

	// 有目标且目标未死亡
	if (Target && !Target->IsDead())
	{
		return;
	}

	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());
	if (PossessAI)
	{
		// 根据配置的选敌规则选敌（这个接口写在基类了）
		Target = SelectTarget(PossessAI->EnemySelectRule, M_EnemyArray);
	}

	M_Blackboard->SetValueAsObject(FName("Target"), Target);
	SetLockedEnemy(Target);

	// 重置 IsPerception，以便 AI 可以巡逻
	M_Blackboard->SetValueAsBool("IsPerception", false);
}

// ------------------------------------------------------ Combat System ----------------------------------------------------------

void AAIController_LongRange::TryApplyDamage()
{
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	if (PossessAI && M_LockedEnemy && !M_LockedEnemy->IsDead())
	{
		float dis = FVector::Distance(PossessAI->GetActorLocation(), M_LockedEnemy->GetActorLocation());
		if (dis <= PossessAI->AttackRadius)
		{
			UGameplayStatics::ApplyDamage(M_LockedEnemy, PossessAI->Atk, this, PossessAI, TSubclassOf<UDamageType>(UDamageType::StaticClass()));

			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is TryApplyDamage() succeed !!!（LongRange）");
		}
	}
}
