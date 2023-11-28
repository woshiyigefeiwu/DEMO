// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Base.h"
#include "Skill_ChangeAttributeValue.generated.h"

UCLASS()
class DEMO1_API ASkill_ChangeAttributeValue : public ASkill_Base
{
	GENERATED_BODY()

// ------------------- Skill Function ----------------------------
public:
	bool CanExecuteSkill(FString SkilleId) override;

	void ExecuteSkill(FString SkilleId) override;

	FSkill_ChangeAttributeValue_Node GetSkillConfigNode(FString SkilleId);
};
