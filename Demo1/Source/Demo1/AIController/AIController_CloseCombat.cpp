// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_CloseCombat.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"

AAIController_CloseCombat::AAIController_CloseCombat()
{
	M_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
	if (M_AIPerception)
	{
		M_AIPerception->ConfigureSense(*SightConfig);
		M_AIPerception->SetDominantSense(SightConfig->GetSenseImplementation());
	}
}

void AAIController_CloseCombat::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAICharacter_Base* AI_CloseCombat = Cast<AAICharacter_Base>(InPawn);

	// 处理一下感知组件
	if (SightConfig)
	{
		// 这一块的配置直接去 AI 上面取就行
		if (AI_CloseCombat)
		{
			SightConfig->SightRadius = AI_CloseCombat->PerceptionRadius;
			SightConfig->LoseSightRadius = AI_CloseCombat->LosePerceptionRadius;
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

	if (AI_CloseCombat)
	{
		AI_CloseCombat->Init();
	}
}

void AAIController_CloseCombat::BeginPlay()
{
	Super::BeginPlay();

	if (M_AIPerception)
	{
		M_AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AAIController_CloseCombat::OnTargetPerceptionUpdated);
	}

	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);
}

void AAIController_CloseCombat::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 更新一下状态
	UpdateState();
}

// --------------------------------------------- AI Behavior Tree ------------------------------------------------

// 更新一下是否进入攻击范围的状态
void AAIController_CloseCombat::UpdateState()
{
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());
	//AAICharacter_Base* TargetEnemy = PossessAI->GetTargetEnemy();

	if (PossessAI == nullptr || PossessAI->IsDead()) return;

	// 目标存在，且未死亡
	if (M_TargetEnemy && !M_TargetEnemy->IsDead())
	{
		// 两者距离 <= 攻击范围
		if (PossessAI->GetDistanceFromEnemy() <= PossessAI->AttackRadius)
		{
			Set_IsInAttackRange(true);		// 设置一下状态
			UpdateBBV_IsInAttackRange();	// 更新黑板值
		}
		else
		{
			Set_IsInAttackRange(false);		// 设置一下状态
			UpdateBBV_IsInAttackRange();	// 更新黑板值
		}
	}
	// 不存在或者死亡，则设置一下 Target 为空，且重置攻击范围状态
	else
	{
		//PossessAI->SetTargetEnemy(nullptr);
		M_TargetEnemy = nullptr;
		UpdateBBV_Target();

		Set_IsInAttackRange(false);
		UpdateBBV_IsInAttackRange();
	}
}

void AAIController_CloseCombat::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//AAICharacter_Base* Enemy = Cast<AAICharacter_Base>(Actor);
	//AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	//// 死亡，同阵营直接跳过
	//if (!Enemy || Enemy->IsDead() || !PossessAI || PossessAI->IsDead() || (Enemy->GetCampType() == PossessAI->GetCampType()))
	//{
	//	return;
	//}

	//// 进入感知
	//if (Stimulus.WasSuccessfullySensed())
	//{
	//	M_Blackboard->SetValueAsBool("IsPerception", true);		// 用于打断巡逻任务

	//	if (!PossessAI->EnemyArray.Contains(Enemy))
	//	{
	//		PossessAI->EnemyArray.Add(Enemy);
	//	}
	//}
	//// 离开感知
	//else
	//{
	//	// 如果当前目标离开，则置空
	//	if (Enemy == PossessAI->GetTargetEnemy())
	//	{
	//		PossessAI->SetTargetEnemy(nullptr);
	//		UpdateBBV_Target();
	//	}

	//	// 如果队列里面有，则删除
	//	if (PossessAI->EnemyArray.Contains(Enemy))
	//	{
	//		PossessAI->EnemyArray.Remove(Enemy);
	//	}
	//}

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
		if (Enemy == M_TargetEnemy)
		{
			//PossessAI->SetTargetEnemy(nullptr);
			M_TargetEnemy = nullptr;
			UpdateBBV_Target();
		}

		// 如果队列里面有，则删除
		if (M_EnemyArray.Contains(Enemy))
		{
			M_EnemyArray.Remove(Enemy);
		}
	}
}

void AAIController_CloseCombat::FindTarget()
{
	if (M_TargetEnemy && !M_TargetEnemy->IsDead())
	{
		return;
	}

	M_TargetEnemy = SelectTarget();
	
	FinishFindTarget();
}

