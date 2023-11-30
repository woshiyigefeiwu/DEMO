// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Base.h"
#include "Skill_ChangeAttributeValue.generated.h"

class AAICharacter_Base;

UCLASS()
class DEMO1_API ASkill_ChangeAttributeValue : public ASkill_Base
{
	GENERATED_BODY()

public:
	void ExecuteSkill(class USkillComponent* SkillComponent, TMap<FString, float> FloatMap, TMap<FString, FSoftClassPath> SoftClassPathMap) override;
};
