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

	// ��ȡ��ǰ AI ��Ŀ�����
	UFUNCTION(BlueprintCallable)
	AAICharacter_Base* GetTargetEnemy();

	// ���õ�ǰ AI ��Ŀ�����
	UFUNCTION()
	void SetTargetEnemy(AAICharacter_Base* NewEnemy);

	// ��ȡ Enemy ����
	UFUNCTION()
	TArray<AAICharacter_Base*> GetEnemyArray();

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

	// �� Target����Ϊ���ҷ�ʽ���ܲ�ͬ����������д��
	UFUNCTION()
	virtual void FindTarget() {};

	// ѡ�У�����ѡ�й�����ò�ͬ��ѡ�з�ʽ��
	UFUNCTION()
	AAICharacter_Base* SelectTarget();

	// �ҵ�һ�����ֵĵ��ˣ���������Լ���д��
	virtual AAICharacter_Base* SelectTarget_First();

	// �Ҿ�������ĵ��ˣ���������Լ���д��
	virtual AAICharacter_Base* SelectTarget_Nearest();

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
protected:
	// �����Ƿ��ڹ�����Χ��
	UPROPERTY()
	bool M_IsInAttackRange;

	// ��ǰ AI �� Ŀ����ˣ�ͬ���ڰ��ֵ��
	UPROPERTY()
	AAICharacter_Base* M_TargetEnemy = nullptr;

	// ��⵽�ĵ���
	UPROPERTY()
	TArray<AAICharacter_Base*> M_EnemyArray;
};
