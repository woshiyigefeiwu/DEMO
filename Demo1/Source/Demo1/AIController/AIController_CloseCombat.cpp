// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_CloseCombat.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

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

	if (SightConfig)
	{
		// ��һ�������ֱ��ȥ AI ����ȡ����
		AAICharacter_CloseCombat* AI_CloseCombat = Cast<AAICharacter_CloseCombat>(InPawn);

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

void AAIController_CloseCombat::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AAICharacter_Base* Enemy = Cast<AAICharacter_Base>(Actor);
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	// ͬ��Ӫֱ������
	if (!Enemy || !PossessAI || (Enemy->GetCampType() == PossessAI->GetCampType()))
	{
		return;
	}

	// �����֪
	if (Stimulus.WasSuccessfullySensed())
	{
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
			PossessAI->SetLockedEnemy(nullptr);
		}

		// ������������У���ɾ��
		if (Enemy && M_EnemyArray.Contains(Enemy))
		{
			M_EnemyArray.Remove(Enemy);
		}
	}

	SetIsPerception(true);
}

void AAIController_CloseCombat::FindTarget()
{
	AAICharacter_Base* Target = Cast<AAICharacter_Base>(M_Blackboard->GetValueAsObject("Target"));
	if (Target)
	{
		return;
	}

	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());
	if (PossessAI)
	{
		// �������õ�ѡ�й���ѡ�У�����ӿ�д�ڻ����ˣ�
		Target = SelectTarget(PossessAI->EnemySelectRule, M_EnemyArray);
	}
	
	if (Target)
	{
		M_Blackboard->SetValueAsObject(FName("Target"), Target);
	}
	PossessAI->SetLockedEnemy(Target);
}

void AAIController_CloseCombat::SetIsPerception(bool flag)
{
	M_Blackboard->SetValueAsBool(FName("IsPerception"), flag);
}