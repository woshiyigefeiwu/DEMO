// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillConfig.h"
#include "SkillComponent.generated.h"

class ASkill_Base;

// 每个技能对应的一张状态表
USTRUCT(BlueprintType)
struct FSkill_State_Node
{
	GENERATED_BODY()
	
	// 上一次释放技能的时间
	double LastReleaseSkillTime = 0.0f;

	// 附加的血量
	float AttachHp = 0.0f;

	// 附加的攻击力
	float AttachAtk = 0.0f;

	// 每个属性可以对应自己的附加值
	TMap<EAttributeType, float> SkillAttributeValueList;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO1_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 获取 SkillManager
	UFUNCTION()
	class ASkillManager* GetSkillManager();

	// 初始化一下技能表
	UFUNCTION()
	void InitSkillStateList();

	// 释放一个技能的流程
	UFUNCTION()
	bool RunExecuteSkill(FString SkillId);

	// 是否能释放技能
	UFUNCTION()
	bool CanExecuteSkill(FString SkillId);

	// 扣除消耗
	UFUNCTION()
	void ReduceSkillConsume(FString SkillId);

	// 对外的释放技能接口
	UFUNCTION()
	void ExecuteSkill(FString SkillId);

	// 尝试触发触发条件为扣血的技能
	void TryExecuteSkillWhenHp();

	// 获取一下属性值
	EAttributeType GetAttributeType(float Value);

// ---------------------------------- 属性表相关操作 -----------------------------------------
public:
	// 获取上次释放技能的时间点
	double GetLastReleaseSkillTime(FString SkillId);

	// 设置上次释放技能的时间点
	void SetLastReleaseSkillTime(FString SkillId, float Value);

	float GetSkillAttributeValueByEAttributeType(FString SkillId, EAttributeType AttributeType);

	void SetSkillAttributeValueByEAttributeType(FString SkillId, EAttributeType AttributeType, float Value);

	float GetTotalSkillAttributeValueByEAttributeType(EAttributeType AttributeType);

public:
	// 收集一下属性
	UFUNCTION(BlueprintCallable)
	TMap<FString, float> CollectFloatConfig(FString SkillId);

	UFUNCTION(BlueprintCallable)
	TMap<FString, FSoftClassPath> CollectSoftClassPathConfig(FString SkillId);

// -------------------------------------------------------------------------------------
public:	
	// 当前组件配置的技能列表
	UPROPERTY(EditAnywhere)
	TArray<FString> SkillList;

	// 每个技能对应的一张状态
	UPROPERTY()
	TMap<FString, FSkill_State_Node> SkillStateList;

	// 缓存一下每个技能的技能效果执行体
	UPROPERTY()
	TMap<FString, ASkill_Base*> SkillExecutorCache;

	UPROPERTY()
	AActor* MyOwner;
};
