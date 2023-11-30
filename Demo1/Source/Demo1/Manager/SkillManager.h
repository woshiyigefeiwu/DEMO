// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo1/Skill/SkillConfig.h"
#include "SkillManager.generated.h"

class ASkill_Base;
class AAICharacter_Base;

UCLASS()
class DEMO1_API ASkillManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 加载类
	UFUNCTION()
	UClass* LoadSkillExecutorClass(FSoftClassPath SoftClassPath);

	// 创建技能执行体
	UFUNCTION()
	ASkill_Base* CreateSkillExecutor(FString SkillId);

	// 获取配置
	UFUNCTION()
	USkillConfig* GetSkillConfig();

	// 判断 Skill 是否在配置表内
	UFUNCTION()
	bool IsInSkillConfigList(FString SkillId);

	// 根据技能Id获取具体的配置
	UFUNCTION()
	FSkill_Config_Node GetSkillConfigNode(FString SkillId);

	// 解析触发消耗配置，并返回消耗列表
	UFUNCTION()
	FString GetSkillConsumeList(FString SkillId);


	// -------------------------------- 触发条件 -------------------------------
	// 根据触发条件中不同的属性类型获取一下值
	float GetValueByAttributeType(EAttributeType AttributeType, AAICharacter_Base* AI);

	// 检查触发条件是否满足
	UFUNCTION()
	bool CheckTriggerCondition(FString SkillId, AActor* Actor);

	// 触发条件类型为 LessThan 的具体判断逻辑（传进来一个触发条件节点）
	bool CheckTriggerCondition_LessThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor);

	// 触发条件类型为 GreaterThan 的具体判断逻辑（传进来一个触发条件节点）
	bool CheckTriggerCondition_GreaterThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor);
};
