// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Base.h"
#include "Perception/AIPerceptionTypes.h"
#include "Demo1/AICharacter/AICharacter_LongRange.h"
#include "AIController_LongRange.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AAIController_LongRange : public AAIController_Base
{
	GENERATED_BODY()

public:
	AAIController_LongRange();

	UFUNCTION()
	void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION()
	void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY()
	class UAIPerceptionComponent* M_AIPerception = nullptr;
};
