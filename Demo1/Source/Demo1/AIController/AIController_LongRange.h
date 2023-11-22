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

	// 更新一下状态（进入追击范围，进入攻击范围）
	//UFUNCTION()
	//void UpdateState();

	// 尝试发出攻击
	//UFUNCTION()
	//void TryAttack();

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	//UFUNCTION(BlueprintCallable)
	//void FindTarget();

	// AI 攻击后的善后处理
	//UFUNCTION()
	//void FinishAttack() override;

	// 清空定时器
	//UFUNCTION()
	//void ClearTimerHandle();

	// 施加伤害
	//UFUNCTION(BlueprintCallable)
	//void TryApplyDamage();

private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig = nullptr;

	UPROPERTY()
	class UAIPerceptionComponent* M_AIPerception = nullptr;

	// 检测到的敌人
	//UPROPERTY()
	//TArray<AAICharacter_Base*> M_EnemyArray;

	// 当前 AI 锁定到的 Enemy AI
	//UPROPERTY()
	//AAICharacter_Base* M_LockedEnemy = nullptr;

	//UPROPERTY()
	//FTimerHandle M_TimerHandle;
};
