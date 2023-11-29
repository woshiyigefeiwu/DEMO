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
	virtual void Init(class USkillComponent* NewSkillComponent, FString SkillId);

	// 技能执行
	virtual void ExecuteSkill(){}

public:	
	// 当前技能效果执行体在哪个技能组件上面
	class USkillComponent* SkillComponent = nullptr;

	// 当前技能效果执行体属于哪个技能（便于修改属性表）
	FString SkillId;
};
