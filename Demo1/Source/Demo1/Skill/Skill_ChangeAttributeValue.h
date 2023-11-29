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
	void ExecuteSkill() override;

	// 辅助函数，获取一下自己需要的配置信息
	TMap<EAttributeType, float> GetAdditionalAttributeList();
};
