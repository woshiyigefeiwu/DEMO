// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillConfig.generated.h"

// ------------------------------------------- 枚举 ---------------------------------------

// 技能类型（同时代表技能的执行逻辑）
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE,
	Attack					= 1		UMETA(DisplayName = "Attack"),
	ChangeAttributeValue	= 2		UMETA(DisplayName = "ChangeAttributeValue"),

	//CloseCombatAttack		= 1		UMETA(DisplayName = "CloseCombatAttack"),
	//LongRangeAttack			= 2		UMETA(DisplayName = "LongRangeAttack"),
};

// 触发条件类型
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan				= 1		UMETA(DisplayName = "LessThan"),
};

// 触发消耗类型
UENUM(BlueprintType)
enum class ETriggerConsume : uint8
{
	NONE,
	AttributeConsume		= 1		UMETA(DisplayName = "AttributeConsume"),	// 属性消耗，比如 蓝，血量 等
	//SkillCD				= 2		UMETA(DisplayName = "技能CD"),
};

// 作用对象类型
UENUM(BlueprintType)
enum class EActionObject : uint8
{
	NONE,
	SELF = 1		UMETA(DisplayName = "Self"),
};

// 属性类型
UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	NONE,
	HP			= 1		UMETA(DisplayName = "HP"),			// 对应血量变化
	ATK			= 2		UMETA(DisplayName = "ATK"),			// 对应攻击力变化
	AttachHP	= 3		UMETA(DisplayName = "AttachHP"),
	AttachATK	= 4		UMETA(DisplayName = "AttachATK"),
};


// ------------------------------------------- 结构体 ---------------------------------------

USTRUCT(BlueprintType)
struct FArrayString_Node
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Array;
};

USTRUCT(BlueprintType)
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttributeType Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

	// ------------------------------------- 附加属性技能的结构体（一个结构体实例代表一种技能）
USTRUCT(BlueprintType)
struct FSkill_ChangeAttributeValue_Node
{
	GENERATED_BODY()

	// 触发条件类型
	UPROPERTY(EditAnywhere)
	ETriggerCondition TriggerCondition;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "TriggerCondition == ETriggerCondition::LessThan", EditConditionHides))
	FAttributeValue AttributeValue;

	// 触发消耗类型
	UPROPERTY(EditAnywhere)
	ETriggerConsume TriggerConsume;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "TriggerConsume == ETriggerConsume::AttributeConsume", EditConditionHides))
	TMap<EAttributeType, float> ConsumeList;
	 
	// 作用对象
	UPROPERTY(EditAnywhere)
	EActionObject ActionObject;

	// 触发效果（属性附加值）
	UPROPERTY(EditAnywhere)
	TMap<EAttributeType, float> AttributeEffectList;
};

	// ----------------------------------------------- 攻击的结构体 -----------------------------------------------------
USTRUCT(BlueprintType)
struct FSkill_Attack_Node
{
	GENERATED_BODY()

	// 触发条件类型
	UPROPERTY(EditAnywhere)
	ETriggerCondition TriggerCondition;

	// 触发消耗类型
	UPROPERTY(EditAnywhere)
	ETriggerConsume TriggerConsume;
	 
	// 作用对象
	UPROPERTY(EditAnywhere)
	EActionObject ActionObject;

	// 技能CD
	UPROPERTY(EditAnywhere)
	float SkillCD;

	// 是否有生成物
	UPROPERTY(EditAnywhere)
	bool IsProduct;

	// 生成物的蓝图类
	UPROPERTY(EditAnywhere, meta = (EditCondition = "IsProduct", EditConditionHides))
	FSoftClassPath ProjectileClassPath;
};

// --------------------------------------------------------------------------------

UCLASS()
class DEMO1_API USkillConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// 每种技能执行逻辑对应一个id（类型就是id）
	UPROPERTY(EditAnywhere, Category = "SkillType")
	TMap<ESkillType, FSoftClassPath> SkillLogicIdConfig;
	
	// 附加属性的技能
	UPROPERTY(EditAnywhere, Category = "ChangeAttributeValue")
	TMap<FString, FSkill_ChangeAttributeValue_Node> Skill_ChangeAttributeValue_List;

	// 攻击技能
	UPROPERTY(EditAnywhere, Category = "Attack")
	TMap<FString, FSkill_Attack_Node> Skill_Attack_List;

};
