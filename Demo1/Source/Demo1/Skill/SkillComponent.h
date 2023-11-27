// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

// ------------------------------------------- ö�� ---------------------------------------

// �������ͣ������Ӧ����Ϊһ�ּ������ͣ�
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE,
	CloseCombatAttack		 = 1	UMETA(DisplayName = "��ս����"),
	LongRangeAttack			 = 2	UMETA(DisplayName = "Զ�̹���"),
	ChangeAttributeValue	 = 3	UMETA(DisplayName = "�ı�����ֵ"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan		= 1		UMETA(DisplayName = "���Ե���"),
};

// ������������
UENUM(BlueprintType)
enum class ETriggerConsume : uint8
{
	NONE,
	//SkillCD			= 1		UMETA(DisplayName = "����CD"),
};

// ���ö�������
UENUM(BlueprintType)
enum class EActionObject : uint8
{
	NONE,
	SELF			= 1		UMETA(DisplayName = "Self"),
};

// ��������
UENUM(BlueprintType)
enum class EAttribute : uint8
{
	NONE,
	HP				= 1		UMETA(DisplayName = "Ѫ��"),		// ��ӦѪ���仯
	ATK				= 2		UMETA(DisplayName = "������"),		// ��Ӧ�������仯
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

	void CreateSkill();

	UClass* LoadSkillClass(FSoftClassPath SoftClassPath);

public:	
	UPROPERTY(EditAnywhere)
	TArray<FSoftClassPath> SkillList;

private:
	UPROPERTY()
	AActor* Owner;

	
};
