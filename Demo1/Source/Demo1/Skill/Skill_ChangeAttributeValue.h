// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill_Base.h"
#include "Skill_ChangeAttributeValue.generated.h"

UCLASS()
class DEMO1_API ASkill_ChangeAttributeValue : public ASkill_Base
{
	GENERATED_BODY()

public:
	// 触发的条件
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition", meta = (EditCondition = "TriggerCondition == ETriggerCondition::LessThan", EditConditionHides))
	FAttributeValue AttributeValue;

	// 消耗的属性
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerConsume", meta = (EditCondition = "TriggerConsume == ETriggerConsume::AttributeConsume", EditConditionHides))
	TMap<EAttribute, float> ConsumeList;

	// 触发效果（属性附加值）
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|AttributeEffectList")
	TMap<EAttribute, float> AttributeEffectList;
};
