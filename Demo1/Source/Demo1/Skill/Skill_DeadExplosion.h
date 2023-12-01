// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Base.h"
#include "Skill_DeadExplosion.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API ASkill_DeadExplosion : public ASkill_Base
{
	GENERATED_BODY()

public:
	void ExecuteSkill(class USkillComponent* SkillComponent, TMap<FString, float> FloatMap, TMap<FString, FSoftClassPath> SoftClassPathMap) override;

	void CreateExplosionObject(class AAICharacter_Base* AI, FSoftClassPath ExplosionSoftClassPath, float AfterExplosionTime, FVector ExplosionRange);
};
