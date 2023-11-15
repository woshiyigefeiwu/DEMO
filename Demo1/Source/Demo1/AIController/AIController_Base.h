// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController_Base.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AAIController_Base : public AAIController
{
	GENERATED_BODY()
	
public:
	AAIController_Base();

	void OnPossess(APawn* InPawn) override;

	void BeginPlay() override;

	UFUNCTION()
	AAICharacter_Base* SelectTarget(EEnemySelectRule SelectRule, TArray<AAICharacter_Base*> AI_Array);

	// 找第一个发现的敌人
	virtual AAICharacter_Base* SelectTarget_First(TArray<AAICharacter_Base*> AI_Array);

	// 找距离最近的敌人
	virtual AAICharacter_Base* SelectTarget_Nearest(TArray<AAICharacter_Base*> AI_Array);

public:


private:
	UPROPERTY()
	class UBehaviorTreeComponent* M_BehaviorTree;

	UPROPERTY()
	class UBlackboardComponent* M_Blackboard;




};
