// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillManager.generated.h"

class ASkill_Base;

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
enum class EAttribute : uint8
{
	NONE,
	HP = 1		UMETA(DisplayName = "HP"),		// ��ӦѪ���仯
	ATK = 2		UMETA(DisplayName = "ATK"),		// ��Ӧ�������仯
};


// ------------------------------------------- �ṹ�� ---------------------------------------

USTRUCT(BlueprintType)
struct FAttributeValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};

// --------------------------------------------------------------------------------

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

	UFUNCTION()
	ASkill_Base* CreateSkill(FString SkillId);

	UFUNCTION()
	UClass* LoadSkillClass(FSoftClassPath SoftClassPath);

public:	
	// ÿ�ּ��ܶ�Ӧһ������id
	UPROPERTY(EditAnywhere)
	TMap<FString, FSoftClassPath> SkillIdConfig;
};
