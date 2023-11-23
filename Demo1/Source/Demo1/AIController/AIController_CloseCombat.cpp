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

	// ����һ�¸�֪���
	if (SightConfig)
	{
		// ��һ�������ֱ��ȥ AI ����ȡ����
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

	// ����һ��״̬
	UpdateState();
}

// --------------------------------------------- AI Behavior Tree ------------------------------------------------

// ����һ���Ƿ���빥����Χ��״̬
void AAIController_CloseCombat::UpdateState()
{
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());
	//AAICharacter_Base* TargetEnemy = PossessAI->GetTargetEnemy();

	if (PossessAI == nullptr || PossessAI->IsDead()) return;

	// Ŀ����ڣ���δ����
	if (M_TargetEnemy && !M_TargetEnemy->IsDead())
	{
		// ���߾��� <= ������Χ
		if (PossessAI->GetDistanceFromEnemy() <= PossessAI->AttackRadius)
		{
			Set_IsInAttackRange(true);		// ����һ��״̬
			UpdateBBV_IsInAttackRange();	// ���ºڰ�ֵ
		}
		else
		{
			Set_IsInAttackRange(false);		// ����һ��״̬
			UpdateBBV_IsInAttackRange();	// ���ºڰ�ֵ
		}
	}
	// �����ڻ���������������һ�� Target Ϊ�գ������ù�����Χ״̬
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

	//// ������ͬ��Ӫֱ������
	//if (!Enemy || Enemy->IsDead() || !PossessAI || PossessAI->IsDead() || (Enemy->GetCampType() == PossessAI->GetCampType()))
	//{
	//	return;
	//}

	//// �����֪
	//if (Stimulus.WasSuccessfullySensed())
	//{
	//	M_Blackboard->SetValueAsBool("IsPerception", true);		// ���ڴ��Ѳ������

	//	if (!PossessAI->EnemyArray.Contains(Enemy))
	//	{
	//		PossessAI->EnemyArray.Add(Enemy);
	//	}
	//}
	//// �뿪��֪
	//else
	//{
	//	// �����ǰĿ���뿪�����ÿ�
	//	if (Enemy == PossessAI->GetTargetEnemy())
	//	{
	//		PossessAI->SetTargetEnemy(nullptr);
	//		UpdateBBV_Target();
	//	}

	//	// ������������У���ɾ��
	//	if (PossessAI->EnemyArray.Contains(Enemy))
	//	{
	//		PossessAI->EnemyArray.Remove(Enemy);
	//	}
	//}

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
		if (Enemy == M_TargetEnemy)
		{
			//PossessAI->SetTargetEnemy(nullptr);
			M_TargetEnemy = nullptr;
			UpdateBBV_Target();
		}

		// ������������У���ɾ��
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

