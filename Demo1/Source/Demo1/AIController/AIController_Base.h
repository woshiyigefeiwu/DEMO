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

	// 获取当前 AI 的目标敌人
	UFUNCTION(BlueprintCallable)
	AAICharacter_Base* GetTargetEnemy();

	// 设置当前 AI 的目标敌人
	UFUNCTION()
	void SetTargetEnemy(AAICharacter_Base* NewEnemy);

	// 获取 Enemy 数组
	UFUNCTION()
	TArray<AAICharacter_Base*> GetEnemyArray();

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

	// 找 Target（因为查找方式可能不同，派生类重写）
	UFUNCTION()
	virtual void FindTarget() {};

	// 选敌（根据选敌规则调用不同的选敌方式）
	UFUNCTION()
	AAICharacter_Base* SelectTarget();

	// 找第一个发现的敌人（派生类可自己重写）
	virtual AAICharacter_Base* SelectTarget_First();

	// 找距离最近的敌人（派生类可自己重写）
	virtual AAICharacter_Base* SelectTarget_Nearest();

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
protected:
	// 敌人是否在攻击范围内
	UPROPERTY()
	bool M_IsInAttackRange;

	// 当前 AI 的 目标敌人（同步黑板键值）
	UPROPERTY()
	AAICharacter_Base* M_TargetEnemy = nullptr;

	// 检测到的敌人
	UPROPERTY()
	TArray<AAICharacter_Base*> M_EnemyArray;
};
