// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

// ------------------------------------------- 枚举 ---------------------------------------

// 技能类型（这个更应该作为一种技能类型）
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	NONE,
	CloseCombatAttack		 = 1	UMETA(DisplayName = "近战攻击"),
	LongRangeAttack			 = 2	UMETA(DisplayName = "远程攻击"),
	ChangeAttributeValue	 = 3	UMETA(DisplayName = "改变属性值"),
};

// 触发条件类型
UENUM(BlueprintType)
enum class ETriggerCondition : uint8
{
	NONE,
	LessThan		= 1		UMETA(DisplayName = "属性低于"),
};

// 触发消耗类型
UENUM(BlueprintType)
enum class ETriggerConsume : uint8
{
	NONE,
	//SkillCD			= 1		UMETA(DisplayName = "技能CD"),
};

// 作用对象类型
UENUM(BlueprintType)
enum class EActionObject : uint8
{
	NONE,
	SELF			= 1		UMETA(DisplayName = "Self"),
};

// 属性类型
UENUM(BlueprintType)
enum class EAttribute : uint8
{
	NONE,
	HP				= 1		UMETA(DisplayName = "血量"),		// 对应血量变化
	ATK				= 2		UMETA(DisplayName = "攻击力"),		// 对应攻击力变化
};


// ------------------------------------------- 结构体 ---------------------------------------

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
