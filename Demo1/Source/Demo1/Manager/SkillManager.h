// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo1/Skill/SkillConfig.h"
#include "SkillManager.generated.h"

class ASkill_Base;
class AAICharacter_Base;

/*
// ------------------------------------------- 枚举 ---------------------------------------

// 技能类型（这个更应该作为一种技能类型）
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE,
	CloseCombatAttack = 1	UMETA(DisplayName = "CloseCombatAttack"),
	LongRangeAttack = 2	UMETA(DisplayName = "LongRangeAttack"),
	ChangeAttributeValue = 3	UMETA(DisplayName = "ChangeAttributeValue"),
};

// 触发条件类型
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan = 1		UMETA(DisplayName = "LessThan"),
};

// 触发消耗类型
UENUM(BlueprintType)
enum class ETriggerConsume : uint8
{
	NONE,
	AttributeConsume	= 1		UMETA(DisplayName = "AttributeConsume"),	// 属性消耗，比如 蓝，血量 等
	//SkillCD			= 2		UMETA(DisplayName = "技能CD"),
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
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttributeType Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

// --------------------------------------------------------------------------------
*/

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

//public:
	//UFUNCTION()
	//ASkill_Base* CreateSkill(ESkillType SkillId);

	//UFUNCTION()
	//float GetFloatAttributeValueByAttributeType(EAttributeType AttributeType, AAICharacter_Base* AI);

	//UFUNCTION()
	//void SetFloatAttributeValueByAttributeType(EAttributeType AttributeType, float Value, AAICharacter_Base* AI);

	//UFUNCTION()
	//FSkill_ChangeAttributeValue_Node GetSkill_ChangeAttributeValue_Node(ESkillType SkillType, FString SkilleId);

// ------------------------------------ 下面是重写 ----------------------------
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
