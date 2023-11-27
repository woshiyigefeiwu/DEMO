// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo1/Manager/SkillManager.h"
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

// ------------------------ Skill Function----------------------------

	// 释放当前的技能
	virtual void ReleaseSkill();

	// 判断是否能释放技能
	virtual bool CanReleaseSkill(){return false;}

	// 扣除消耗
	virtual void ReduceConsume(){}

	// 技能执行
	virtual void ExecuteSkill(){}

// ------------------------ Skill Property----------------------------
public:	
	// 当前技能对象在哪个技能组件上面
	class USkillComponent* SkillComponent;


public:
	// 触发条件类型
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerCondition")
	ETriggerCondition TriggerCondition;

	// 触发消耗类型
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|TriggerConsume")
	ETriggerConsume TriggerConsume;

	// 作用对象
	UPROPERTY(EditAnywhere, Category = "SkilleConfig|ActionObject")
	EActionObject ActionObject;

	// 当前技能的类型（从外部赋一下值）
	//UPROPERTY(BlueprintReadOnly, Category = "SkilleConfig")
	//ESkillType SkillType;
};
