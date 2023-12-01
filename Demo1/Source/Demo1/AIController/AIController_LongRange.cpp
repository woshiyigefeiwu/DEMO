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
}

// --------------------------------------------- AI Behavior Tree ------------------------------------------------

void AAIController_LongRange::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	AAICharacter_Base* Enemy = Cast<AAICharacter_Base>(Actor);
	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());

	// 死亡，同阵营直接跳过
	if (!Enemy || Enemy->IsDead() || !PossessAI || PossessAI->IsDead() || (Enemy->GetCampType() == PossessAI->GetCampType()))
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		// 
		//float dis1 = FVector::Distance(PossessAI->GetActorLocation(), M_TargetEnemy->GetActorLocation());
		//float dis2 = FVector::Distance(PossessAI->GetActorLocation(), Enemy->GetActorLocation());
		//if (dis2 < dis1)
		//{
			M_TargetEnemy = Enemy;
		//}
	}
	else if (M_TargetEnemy == Enemy)
	{
		M_Blackboard->SetValueAsVector("EnemyLocation", M_TargetEnemy->GetActorLocation());
		M_TargetEnemy = nullptr;
	}

	UpdateBBV_Target();
}

void AAIController_LongRange::FindTarget()
{
	if (M_TargetEnemy && !M_TargetEnemy->IsDead())
	{
		return;
	}

	M_TargetEnemy = SelectTarget();

	UpdateBBV_Target();

	// 重置 IsPerception，以便 AI 可以巡逻
	M_Blackboard->SetValueAsBool("IsPerception", false);
}

void AAIController_LongRange::InitAIPerception(APawn* InPawn)
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(InPawn);

	// 处理一下感知组件
	if (SightConfig)
	{
		// 这一块的配置直接去 AI 上面取就行
		if (AI)
		{
			SightConfig->SightRadius = AI->PerceptionRadius;
			SightConfig->LoseSightRadius = AI->LosePerceptionRadius;
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



