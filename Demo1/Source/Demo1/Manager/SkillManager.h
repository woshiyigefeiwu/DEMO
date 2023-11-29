// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo1/Skill/SkillConfig.h"
#include "SkillManager.generated.h"

class ASkill_Base;
class AAICharacter_Base;

/*
// ------------------------------------------- ö�� ---------------------------------------

// �������ͣ������Ӧ����Ϊһ�ּ������ͣ�
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE,
	CloseCombatAttack = 1	UMETA(DisplayName = "CloseCombatAttack"),
	LongRangeAttack = 2	UMETA(DisplayName = "LongRangeAttack"),
	ChangeAttributeValue = 3	UMETA(DisplayName = "ChangeAttributeValue"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan = 1		UMETA(DisplayName = "LessThan"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerConsume : uint8
{
	NONE,
	AttributeConsume	= 1		UMETA(DisplayName = "AttributeConsume"),	// �������ģ����� ����Ѫ�� ��
	//SkillCD			= 2		UMETA(DisplayName = "����CD"),
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

// ------------------------------------ ��������д ----------------------------
public:
	// ������
	UFUNCTION()
	UClass* LoadSkillExecutorClass(FSoftClassPath SoftClassPath);

	// ��������ִ����
	UFUNCTION()
	ASkill_Base* CreateSkillExecutor(FString SkillId);

	// ��ȡ����
	UFUNCTION()
	USkillConfig* GetSkillConfig();

	// �ж� Skill �Ƿ������ñ���
	UFUNCTION()
	bool IsInSkillConfigList(FString SkillId);

	// ���ݼ���Id��ȡ���������
	UFUNCTION()
	FSkill_Config_Node GetSkillConfigNode(FString SkillId);

	// ���������������ã������������б�
	UFUNCTION()
	FString GetSkillConsumeList(FString SkillId);


	// -------------------------------- �������� -------------------------------
	// ���ݴ��������в�ͬ���������ͻ�ȡһ��ֵ
	float GetValueByAttributeType(EAttributeType AttributeType, AAICharacter_Base* AI);

	// ��鴥�������Ƿ�����
	UFUNCTION()
	bool CheckTriggerCondition(FString SkillId, AActor* Actor);

	// ������������Ϊ LessThan �ľ����ж��߼���������һ�����������ڵ㣩
	bool CheckTriggerCondition_LessThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor);

	// ������������Ϊ GreaterThan �ľ����ж��߼���������һ�����������ڵ㣩
	bool CheckTriggerCondition_GreaterThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor);
};
