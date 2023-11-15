// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Base.h"
#include "AIController_CloseCombat.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AAIController_CloseCombat : public AAIController_Base
{
	GENERATED_BODY()
	
public:
	AAIController_CloseCombat();

	UFUNCTION()
	void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void BeginPlay() override;

private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY()
	class UAIPerceptionComponent* M_AIPerception = nullptr;

	//UPROPERTY()
	//FTimerHandle M_TimerHandle;
};
