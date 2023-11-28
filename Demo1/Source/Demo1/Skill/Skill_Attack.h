// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Base.h"
#include "Skill_Attack.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API ASkill_Attack : public ASkill_Base
{
	GENERATED_BODY()

// ------------------- Skill Function ----------------------------
public:
	bool CanExecuteSkill(FString SkilleId) override;

	void ExecuteSkill(FString SkilleId) override;

	FSkill_Attack_Node GetSkillConfigNode(FString SkilleId);

public:
	// 定时器，用于处理攻击CD
	UPROPERTY()
	FTimerHandle AttackTimerHandle;
};
