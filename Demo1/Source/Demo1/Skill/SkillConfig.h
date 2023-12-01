// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillConfig.generated.h"

// ------------------------------------------- 枚举 ---------------------------------------

// 技能类型（同时代表技能的执行逻辑）
UENUM(BlueprintType)
enum class ESkillEffectType : uint8
{
	NONE,
	Attack					= 1		UMETA(DisplayName = "Attack"),
	ChangeAttributeValue	= 2		UMETA(DisplayName = "ChangeAttributeValue"),
};

// 触发条件类型
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan				= 1		UMETA(DisplayName = "LessThan"),
	GreaterThan				= 2		UMETA(DisplayName = "GreaterThan"),
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
	Friend = 2		UMETA(DisplayName = "Friend"),
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
	TotalHp		= 5		UMETA(DisplayName = "TotalHp"),
	TotalAtk = 5		UMETA(DisplayName = "TotalAtk"),
};


// ------------------------------------------- 结构体 ---------------------------------------

USTRUCT(BlueprintType)
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttributeType Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

// 触发条件
USTRUCT(BlueprintType)
struct FSkill_Config_Condition_Node
{
	GENERATED_BODY()

	// 触发条件类型
	UPROPERTY(EditAnywhere, Category = "TriggerCondition")
	ETriggerCondition TriggerConditionType;

	// 具体触发条件
	UPROPERTY(EditAnywhere, Category = "TriggerCondition", meta = (EditCondition = "TriggerConditionType != ETriggerCondition::NONE", EditConditionHides))
	FAttributeValue TriggerConditionAttributeValue;
};

// 触发消耗
USTRUCT(BlueprintType)
struct FSkill_Config_Consume_Node
{
	GENERATED_BODY()

	// 触发消耗类型
	UPROPERTY(EditAnywhere, Category = "TriggerConsume")
	ETriggerConsume TriggerConsumeType;
};

// 触发效果 ------------------ 属性附加值
//USTRUCT(BlueprintType)
//struct FSkill_Config_Effect_AdditionalAttribute_Node
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, Category = "SkillEffect|AdditionalAttribute")
//	TMap<EAttributeType, float> AdditionalAttributeList;
//};

// 触发效果 ------------------ 攻击
//USTRUCT(BlueprintType)
//struct FSkill_Config_Effect_Attack_Node
//{
//	GENERATED_BODY()
//
//	// 是否有发射物
//	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack")
//	bool IsHasProjectile;			
//
//	// 发射物的BP
//	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack", meta = (EditCondition = "IsHasProjectile", EditConditionHides))
//	FSoftClassPath ProjectileClassPath;
//};

// 触发效果 ------------------ 自爆
USTRUCT(BlueprintType)
struct FSkill_Config_Effect_SelfExplosion_Node
{
	GENERATED_BODY()

	// 爆炸物
	UPROPERTY(EditAnywhere)
	FSoftClassPath ExplosionObjectClassPath;

	// 多少秒后自爆
	UPROPERTY(EditAnywhere)
	float ExplosionTime;
	
	// 爆炸范围
	UPROPERTY(EditAnywhere)
	FVector ExplosionRange;
};

// 触发效果
USTRUCT(BlueprintType)
struct FSkill_Config_Effect_Node
{
	GENERATED_BODY()

	// 触发效果类型
	//UPROPERTY(EditAnywhere, Category = "SkillEffect")
	//ESkillEffectType SkillEffectType;

	// 触发效果执行体
	UPROPERTY(EditAnywhere, Category = "SkillEffect")
	FSoftClassPath SkillEffectExecutor;

	//UPROPERTY(EditAnywhere, Category = "SkillEffect|AdditionalAttribute", meta = (EditCondition = "SkillEffectType == ESkillEffectType::ChangeAttributeValue", EditConditionHides))
	//FSkill_Config_Effect_AdditionalAttribute_Node Skill_Config_Effect_AdditionalAttribute_Node;

	//UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack", meta = (EditCondition = "SkillEffectType == ESkillEffectType::Attack", EditConditionHides))
	//FSkill_Config_Effect_Attack_Node Skill_Config_Effect_Attack_Node;

	// 触发效果 ------------------ 属性附加值
	UPROPERTY(EditAnywhere, Category = "SkillEffect|AdditionalAttribute")
	TMap<EAttributeType, float> AdditionalAttributeList;

	// 触发效果 ------------------ 攻击
	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack")
	bool IsHasProjectile;					// 是否有发射物

	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack", meta = (EditCondition = "IsHasProjectile", EditConditionHides))
	FSoftClassPath ProjectileClassPath;		// 发射物的 BP

	// 触发效果 ------------------- 自爆
	UPROPERTY(EditAnywhere, Category = "SkillEffect|SelfExplosion")
	FSkill_Config_Effect_SelfExplosion_Node Skill_Config_Effect_SelfExplosion_Node;
};

// 其他配置
USTRUCT(BlueprintType)
struct FSkill_Config_Other_Node
{
	GENERATED_BODY()

	// 作用对象
	UPROPERTY(EditAnywhere, Category = "OtherConfig")
	EActionObject ActionObject;

	// 技能CD
	UPROPERTY(EditAnywhere, Category = "OtherConfig")
	float SkillCD;
};

USTRUCT(BlueprintType)
struct FSkill_Config_Node
{
	GENERATED_BODY()

	// 触发条件
	UPROPERTY(EditAnywhere, Category = TriggerCondition)
	FSkill_Config_Condition_Node TriggerCondition;

	// 触发消耗
	UPROPERTY(EditAnywhere, Category = TriggerConsume)
	FSkill_Config_Consume_Node TriggerConsume;

	// 触发效果
	UPROPERTY(EditAnywhere, Category = SkillEffect)
	FSkill_Config_Effect_Node TriggerEffect;
	
	// 其他配置
	UPROPERTY(EditAnywhere, Category = SkillEffect)
	FSkill_Config_Other_Node OtherConfig;
};

// --------------------------------------------------------------------------------

UCLASS()
class DEMO1_API USkillConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// 每种技能对应一个结构体配置
	UPROPERTY(EditAnywhere)
	TMap<FString, FSkill_Config_Node> SkillConfigList;
};