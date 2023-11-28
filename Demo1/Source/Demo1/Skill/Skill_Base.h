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
	virtual void Init(class USkillComponent* NewSkillComponent, ESkillType NewSkillType);

// ------------------------ Skill Function----------------------------

	// 释放当前的技能
	virtual void PreExecuteSkill(FString SkilleId);

	// 判断是否能释放技能
	virtual bool CanExecuteSkill(FString SkilleId){return false;}

	// 扣除消耗
	virtual void ReduceConsume(FString SkilleId){}

	// 技能执行
	virtual void ExecuteSkill(FString SkilleId){}

// ------------------------ Skill Property----------------------------
public:	
	// 当前技能对象在哪个技能组件上面
	class USkillComponent* SkillComponent = nullptr;

	// 当前技能的类型
	ESkillType SkillType;
};
