// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillComponent.h"
#include "Skill_Base.generated.h"

UCLASS()
class DEMO1_API ASkill_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill_Base();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 初始化
	virtual void Init(class USkillComponent* NewSkillComponent);

public:	
	// 当前技能对象在哪个技能组件上面
	class USkillComponent* SkillComponent;


// ----------------------------------- 先测试一下 --------------------------------
public:
	// 当前技能的类型（从外部赋一下值）
	UPROPERTY(EditAnywhere, Category = "SkilleConfig", meta = (DisplayName = "技能类型"))
	ESkillType SkillType;

	// 触发条件
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition", meta = (DisplayName = "触发条件"))
	ETriggerCondition TriggerCondition;

	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition", meta = (EditCondition = "TriggerCondition == ETriggerCondition::LessThan", EditConditionHides, DisplayName = "属性阈值低于"))
	FAttributeValue AttributeValue;


	// 触发消耗
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerConsume", meta = (DisplayName = "触发消耗"))
	TMap<ETriggerConsume,float> TriggerConsume;


	// 作用对象
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|ActionObject", meta = (DisplayName = "作用对象"))
	EActionObject ActionObject;


	// 触发效果（属性附加值）
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|AttributeEffectList", meta = (EditCondition = "SkillType == ESkillType::ChangeAttributeValue", EditConditionHides, DisplayName = "属性附加值"))
	TMap<EAttribute, float> AttributeEffectList;
};
