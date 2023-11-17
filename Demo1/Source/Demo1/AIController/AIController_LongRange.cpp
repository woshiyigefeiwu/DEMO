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

	// ����һ�¸�֪���
	if (SightConfig)
	{
		// ��һ�������ֱ��ȥ AI ����ȡ����
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

	// ����һ��״̬
	UpdateState();

	// ���Է�������
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

// ����һ���Ƿ���빥����Χ��״̬
void AAIController_LongRange::UpdateState()
{
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	if (PossessAI == nullptr || PossessAI->IsDead()) return;

	// Ŀ����ڣ���δ����
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
	// �����ڻ���������������һ�� Target Ϊ�գ������ù�����Χ״̬
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

// ���Է�������
void AAIController_LongRange::TryAttack()
{
	AAICharacter_LongRange* PossessAI = Cast<AAICharacter_LongRange>(GetPawn());
	bool IsInAttackRange = GetBlackboard()->GetValueAsBool(FName("IsInAttackRange"));

	// ��ǰ���ڹ�����Χ�ڣ��Ҷ�ʱ��������ڣ��ŷ���һ�ι���
	if (PossessAI && IsInAttackRange && !GetWorldTimerManager().IsTimerActive(M_TimerHandle))
	{
		PossessAI->AttackEnemy();
	}
}

void AAIController_LongRange::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AAICharacter_Base* Enemy = Cast<AAICharacter_Base>(Actor);
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	// ������ͬ��Ӫֱ������
	if (!Enemy || Enemy->IsDead() || !PossessAI || PossessAI->IsDead() || (Enemy->GetCampType() == PossessAI->GetCampType()))
	{
		return;
	}

	// �����֪
	if (Stimulus.WasSuccessfullySensed())
	{
		M_Blackboard->SetValueAsBool("IsPerception", true);		// ���ڴ��Ѳ������

		if (!M_EnemyArray.Contains(Enemy))
		{
			M_EnemyArray.Add(Enemy);
		}
	}
	// �뿪��֪
	else
	{
		// �����ǰĿ���뿪�����ÿ�
		if (Actor == M_Blackboard->GetValueAsObject("Target"))
		{
			M_Blackboard->SetValueAsObject("Target", nullptr);
			SetLockedEnemy(nullptr);
		}

		// ������������У���ɾ��
		if (M_EnemyArray.Contains(Enemy))
		{
			M_EnemyArray.Remove(Enemy);
		}
	}
}

void AAIController_LongRange::FindTarget()
{
	AAICharacter_Base* Target = Cast<AAICharacter_Base>(M_Blackboard->GetValueAsObject("Target"));

	// ��Ŀ����Ŀ��δ����
	if (Target && !Target->IsDead())
	{
		return;
	}

	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());
	if (PossessAI)
	{
		// �������õ�ѡ�й���ѡ�У�����ӿ�д�ڻ����ˣ�
		Target = SelectTarget(PossessAI->EnemySelectRule, M_EnemyArray);
	}

	M_Blackboard->SetValueAsObject(FName("Target"), Target);
	SetLockedEnemy(Target);

	// ���� IsPerception���Ա� AI ����Ѳ��
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

			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is TryApplyDamage() succeed !!!��LongRange��");
		}
	}
}
