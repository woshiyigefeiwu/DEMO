// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
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

// ---------------------------------- Init，Get，Set，Check 函数 --------------------------------------
public:
	// 获取黑板
	UFUNCTION()
	UBlackboardComponent* GetBlackboard();

	// 初始化一些黑板值
	UFUNCTION()
	virtual void InitBlackboardValue();

	// 获取攻击范围状态
	UFUNCTION(BlueprintCallable)
	bool Get_IsInAttackRange();

	// 设置攻击范围状态
	UFUNCTION()
	void Set_IsInAttackRange(bool State);

// -------------------------------------------- 辅助函数 -----------------------------------
public:
	// 运行 行为树
	UFUNCTION()
	void RunAIBehaviorTree(APawn* InPawn);

	// 绑一些AI身上的委托
	UFUNCTION()
	void BindDelegateFromAI(APawn* InPawn);

	// 更新黑板值 IsPerception
	UFUNCTION()
	void UpdateBBV_IsInAttackRange();

	// 更新黑板值 Target
	UFUNCTION()
	void UpdateBBV_Target();

// -------------------------------------------- Event ------------------------------------
public:
	// AI 找完 Target 之后的事件
	UFUNCTION()
	void FinishFindTarget();

protected:
	UPROPERTY()
	class UBehaviorTreeComponent* M_BehaviorTree;

	UPROPERTY()
	class UBlackboardComponent* M_Blackboard;

// ------------------------------------------- Blackboard Value -------------------------
private:
	// 敌人是否在攻击范围内
	bool M_IsInAttackRange;
};
