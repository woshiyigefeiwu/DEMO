// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_CloseCombat.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Demo1/AICharacter/AICharacter_CloseCombat.h"

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

		//if (AI_CloseCombat && )
		//{

		//}
		//else
		//{
		//	SightConfig->SightRadius = 3000;
		//	SightConfig->LoseSightRadius = 3500;
		//}

		SightConfig->PeripheralVisionAngleDegrees = 180.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		//SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
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
}
