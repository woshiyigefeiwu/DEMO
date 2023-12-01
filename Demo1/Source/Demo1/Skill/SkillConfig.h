// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillConfig.generated.h"

// ------------------------------------------- ö�� ---------------------------------------

// �������ͣ�ͬʱ�����ܵ�ִ���߼���
UENUM(BlueprintType)
enum class ESkillEffectType : uint8
{
	NONE,
	Attack					= 1		UMETA(DisplayName = "Attack"),
	ChangeAttributeValue	= 2		UMETA(DisplayName = "ChangeAttributeValue"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan				= 1		UMETA(DisplayName = "LessThan"),
	GreaterThan				= 2		UMETA(DisplayName = "GreaterThan"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerConsume : uint8
{
	NONE,
	AttributeConsume		= 1		UMETA(DisplayName = "AttributeConsume"),	// �������ģ����� ����Ѫ�� ��
	//SkillCD				= 2		UMETA(DisplayName = "����CD"),
};

// ���ö�������
UENUM(BlueprintType)
enum class EActionObject : uint8
{
	NONE,
	SELF = 1		UMETA(DisplayName = "Self"),
	Friend = 2		UMETA(DisplayName = "Friend"),
};

// ��������
UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	NONE,
	HP			= 1		UMETA(DisplayName = "HP"),			// ��ӦѪ���仯
	ATK			= 2		UMETA(DisplayName = "ATK"),			// ��Ӧ�������仯
	AttachHP	= 3		UMETA(DisplayName = "AttachHP"),
	AttachATK	= 4		UMETA(DisplayName = "AttachATK"),
	TotalHp		= 5		UMETA(DisplayName = "TotalHp"),
	TotalAtk = 5		UMETA(DisplayName = "TotalAtk"),
};


// ------------------------------------------- �ṹ�� ---------------------------------------

USTRUCT(BlueprintType)
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttributeType Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

// ��������
USTRUCT(BlueprintType)
struct FSkill_Config_Condition_Node
{
	GENERATED_BODY()

	// ������������
	UPROPERTY(EditAnywhere, Category = "TriggerCondition")
	ETriggerCondition TriggerConditionType;

	// ���崥������
	UPROPERTY(EditAnywhere, Category = "TriggerCondition", meta = (EditCondition = "TriggerConditionType != ETriggerCondition::NONE", EditConditionHides))
	FAttributeValue TriggerConditionAttributeValue;
};

// ��������
USTRUCT(BlueprintType)
struct FSkill_Config_Consume_Node
{
	GENERATED_BODY()

	// ������������
	UPROPERTY(EditAnywhere, Category = "TriggerConsume")
	ETriggerConsume TriggerConsumeType;
};

// ����Ч�� ------------------ ���Ը���ֵ
//USTRUCT(BlueprintType)
//struct FSkill_Config_Effect_AdditionalAttribute_Node
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, Category = "SkillEffect|AdditionalAttribute")
//	TMap<EAttributeType, float> AdditionalAttributeList;
//};

// ����Ч�� ------------------ ����
//USTRUCT(BlueprintType)
//struct FSkill_Config_Effect_Attack_Node
//{
//	GENERATED_BODY()
//
//	// �Ƿ��з�����
//	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack")
//	bool IsHasProjectile;			
//
//	// �������BP
//	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack", meta = (EditCondition = "IsHasProjectile", EditConditionHides))
//	FSoftClassPath ProjectileClassPath;
//};

// ����Ч�� ------------------ �Ա�
USTRUCT(BlueprintType)
struct FSkill_Config_Effect_SelfExplosion_Node
{
	GENERATED_BODY()

	// ��ը��
	UPROPERTY(EditAnywhere)
	FSoftClassPath ExplosionObjectClassPath;

	// ��������Ա�
	UPROPERTY(EditAnywhere)
	float ExplosionTime;
	
	// ��ը��Χ
	UPROPERTY(EditAnywhere)
	FVector ExplosionRange;
};

// ����Ч��
USTRUCT(BlueprintType)
struct FSkill_Config_Effect_Node
{
	GENERATED_BODY()

	// ����Ч������
	//UPROPERTY(EditAnywhere, Category = "SkillEffect")
	//ESkillEffectType SkillEffectType;

	// ����Ч��ִ����
	UPROPERTY(EditAnywhere, Category = "SkillEffect")
	FSoftClassPath SkillEffectExecutor;

	//UPROPERTY(EditAnywhere, Category = "SkillEffect|AdditionalAttribute", meta = (EditCondition = "SkillEffectType == ESkillEffectType::ChangeAttributeValue", EditConditionHides))
	//FSkill_Config_Effect_AdditionalAttribute_Node Skill_Config_Effect_AdditionalAttribute_Node;

	//UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack", meta = (EditCondition = "SkillEffectType == ESkillEffectType::Attack", EditConditionHides))
	//FSkill_Config_Effect_Attack_Node Skill_Config_Effect_Attack_Node;

	// ����Ч�� ------------------ ���Ը���ֵ
	UPROPERTY(EditAnywhere, Category = "SkillEffect|AdditionalAttribute")
	TMap<EAttributeType, float> AdditionalAttributeList;

	// ����Ч�� ------------------ ����
	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack")
	bool IsHasProjectile;					// �Ƿ��з�����

	UPROPERTY(EditAnywhere, Category = "SkillEffect|Attack", meta = (EditCondition = "IsHasProjectile", EditConditionHides))
	FSoftClassPath ProjectileClassPath;		// ������� BP

	// ����Ч�� ------------------- �Ա�
	UPROPERTY(EditAnywhere, Category = "SkillEffect|SelfExplosion")
	FSkill_Config_Effect_SelfExplosion_Node Skill_Config_Effect_SelfExplosion_Node;
};

// ��������
USTRUCT(BlueprintType)
struct FSkill_Config_Other_Node
{
	GENERATED_BODY()

	// ���ö���
	UPROPERTY(EditAnywhere, Category = "OtherConfig")
	EActionObject ActionObject;

	// ����CD
	UPROPERTY(EditAnywhere, Category = "OtherConfig")
	float SkillCD;
};

USTRUCT(BlueprintType)
struct FSkill_Config_Node
{
	GENERATED_BODY()

	// ��������
	UPROPERTY(EditAnywhere, Category = TriggerCondition)
	FSkill_Config_Condition_Node TriggerCondition;

	// ��������
	UPROPERTY(EditAnywhere, Category = TriggerConsume)
	FSkill_Config_Consume_Node TriggerConsume;

	// ����Ч��
	UPROPERTY(EditAnywhere, Category = SkillEffect)
	FSkill_Config_Effect_Node TriggerEffect;
	
	// ��������
	UPROPERTY(EditAnywhere, Category = SkillEffect)
	FSkill_Config_Other_Node OtherConfig;
};

// --------------------------------------------------------------------------------

UCLASS()
class DEMO1_API USkillConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// ÿ�ּ��ܶ�Ӧһ���ṹ������
	UPROPERTY(EditAnywhere)
	TMap<FString, FSkill_Config_Node> SkillConfigList;
};