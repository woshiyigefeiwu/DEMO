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
		// 这一块的配置直接去 AI 上面取就行
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

	// 同阵营直接跳过
	if (!Enemy || !PossessAI || (Enemy->GetCampType() == PossessAI->GetCampType()))
	{
		return;
	}

	// 进入感知
	if (Stimulus.WasSuccessfullySensed())
	{
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
			PossessAI->SetLockedEnemy(nullptr);
		}

		// 如果队列里面有，则删除
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
		// 根据配置的选敌规则选敌（这个接口写在基类了）
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