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

// ---------------------------------- Init��Get��Set��Check ���� --------------------------------------
public:
	// ��ȡ�ڰ�
	UFUNCTION()
	UBlackboardComponent* GetBlackboard();

	// ��ʼ��һЩ�ڰ�ֵ
	UFUNCTION()
	virtual void InitBlackboardValue();

	// ��ȡ������Χ״̬
	UFUNCTION(BlueprintCallable)
	bool Get_IsInAttackRange();

	// ���ù�����Χ״̬
	UFUNCTION()
	void Set_IsInAttackRange(bool State);

// -------------------------------------------- �������� -----------------------------------
public:
	// ���� ��Ϊ��
	UFUNCTION()
	void RunAIBehaviorTree(APawn* InPawn);

	// ��һЩAI���ϵ�ί��
	UFUNCTION()
	void BindDelegateFromAI(APawn* InPawn);

	// ���ºڰ�ֵ IsPerception
	UFUNCTION()
	void UpdateBBV_IsInAttackRange();

	// ���ºڰ�ֵ Target
	UFUNCTION()
	void UpdateBBV_Target();

// -------------------------------------------- Event ------------------------------------
public:
	// AI ���� Target ֮����¼�
	UFUNCTION()
	void FinishFindTarget();

protected:
	UPROPERTY()
	class UBehaviorTreeComponent* M_BehaviorTree;

	UPROPERTY()
	class UBlackboardComponent* M_Blackboard;

// ------------------------------------------- Blackboard Value -------------------------
private:
	// �����Ƿ��ڹ�����Χ��
	bool M_IsInAttackRange;
};
