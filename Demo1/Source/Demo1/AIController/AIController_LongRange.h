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

	//UFUNCTION()
	//AAICharacter_Base* GetLockedEnemy();

	//UFUNCTION()
	//void SetLockedEnemy(AAICharacter_Base* Enemy);

	// ����һ��״̬������׷����Χ�����빥����Χ��
	//UFUNCTION()
	//void UpdateState();

	// ���Է�������
	//UFUNCTION()
	//void TryAttack();

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	//UFUNCTION(BlueprintCallable)
	//void FindTarget();

	// AI ��������ƺ���
	//UFUNCTION()
	//void FinishAttack() override;

	// ��ն�ʱ��
	//UFUNCTION()
	//void ClearTimerHandle();

	// ʩ���˺�
	//UFUNCTION(BlueprintCallable)
	//void TryApplyDamage();

private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY()
	class UAIPerceptionComponent* M_AIPerception = nullptr;

	// ��⵽�ĵ���
	//UPROPERTY()
	//TArray<AAICharacter_Base*> M_EnemyArray;

	// ��ǰ AI �������� Enemy AI
	//UPROPERTY()
	//AAICharacter_Base* M_LockedEnemy = nullptr;

	//UPROPERTY()
	//FTimerHandle M_TimerHandle;
};
