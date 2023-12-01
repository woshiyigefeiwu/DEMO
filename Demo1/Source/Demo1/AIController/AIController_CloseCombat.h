// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController_Base.h"
#include "Perception/AIPerceptionTypes.h"
#include "Demo1/AICharacter/AICharacter_CloseCombat.h"
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

	UFUNCTION()
	void Tick(float DeltaSeconds) override;

	// 更新一下状态（进入追击范围，进入攻击范围）
	UFUNCTION()
	void UpdateState();

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void FindTarget() override;

	// 初始化感知组件
	void InitAIPerception(APawn* InPawn) override;

private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY()
	class UAIPerceptionComponent* M_AIPerception = nullptr;
};
