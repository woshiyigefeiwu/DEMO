// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillConfig.generated.h"

// ------------------------------------------- ö�� ---------------------------------------

// �������ͣ�ͬʱ�����ܵ�ִ���߼���
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE,
	Attack					= 1		UMETA(DisplayName = "Attack"),
	ChangeAttributeValue	= 2		UMETA(DisplayName = "ChangeAttributeValue"),

	//CloseCombatAttack		= 1		UMETA(DisplayName = "CloseCombatAttack"),
	//LongRangeAttack			= 2		UMETA(DisplayName = "LongRangeAttack"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan				= 1		UMETA(DisplayName = "LessThan"),
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
};


// ------------------------------------------- �ṹ�� ---------------------------------------

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

	// ------------------------------------- �������Լ��ܵĽṹ�壨һ���ṹ��ʵ������һ�ּ��ܣ�
USTRUCT(BlueprintType)
struct FSkill_ChangeAttributeValue_Node
{
	GENERATED_BODY()

	// ������������
	UPROPERTY(EditAnywhere)
	ETriggerCondition TriggerCondition;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "TriggerCondition == ETriggerCondition::LessThan", EditConditionHides))
	FAttributeValue AttributeValue;

	// ������������
	UPROPERTY(EditAnywhere)
	ETriggerConsume TriggerConsume;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "TriggerConsume == ETriggerConsume::AttributeConsume", EditConditionHides))
	TMap<EAttributeType, float> ConsumeList;
	 
	// ���ö���
	UPROPERTY(EditAnywhere)
	EActionObject ActionObject;

	// ����Ч�������Ը���ֵ��
	UPROPERTY(EditAnywhere)
	TMap<EAttributeType, float> AttributeEffectList;
};

	// ----------------------------------------------- �����Ľṹ�� -----------------------------------------------------
USTRUCT(BlueprintType)
struct FSkill_Attack_Node
{
	GENERATED_BODY()

	// ������������
	UPROPERTY(EditAnywhere)
	ETriggerCondition TriggerCondition;

	// ������������
	UPROPERTY(EditAnywhere)
	ETriggerConsume TriggerConsume;
	 
	// ���ö���
	UPROPERTY(EditAnywhere)
	EActionObject ActionObject;

	// ����CD
	UPROPERTY(EditAnywhere)
	float SkillCD;

	// �Ƿ���������
	UPROPERTY(EditAnywhere)
	bool IsProduct;

	// ���������ͼ��
	UPROPERTY(EditAnywhere, meta = (EditCondition = "IsProduct", EditConditionHides))
	FSoftClassPath ProjectileClassPath;
};

// --------------------------------------------------------------------------------

UCLASS()
class DEMO1_API USkillConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// ÿ�ּ���ִ���߼���Ӧһ��id�����;���id��
	UPROPERTY(EditAnywhere, Category = "SkillType")
	TMap<ESkillType, FSoftClassPath> SkillLogicIdConfig;
	
	// �������Եļ���
	UPROPERTY(EditAnywhere, Category = "ChangeAttributeValue")
	TMap<FString, FSkill_ChangeAttributeValue_Node> Skill_ChangeAttributeValue_List;

	// ��������
	UPROPERTY(EditAnywhere, Category = "Attack")
	TMap<FString, FSkill_Attack_Node> Skill_Attack_List;

};
