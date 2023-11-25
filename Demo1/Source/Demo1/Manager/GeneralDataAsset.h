// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/Color.h"

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneralDataAsset.generated.h"

// -------------------------------------------- Enum -------------------------------------------

// 阵营
UENUM(BlueprintType)
enum class ECampType : uint8
{
	NONE,
	RED		=	1	UMETA(DisplayName = "Red"),
	BLUE	=	2	UMETA(DisplayName = "Blue"),
};

// 兵种
UENUM(BlueprintType)
enum class ESoldierType : uint8
{
	NONE,
	CLOSECOMBAT		= 1		UMETA(DisplayName = "CloseCombat"),
	LONGRANGE		= 2		UMETA(DisplayName = "LongRange"),
};

// 选敌规则
UENUM(BlueprintType)
enum class EEnemySelectRule : uint8
{
	NONE,
	FIRST		= 1		UMETA(DisplayName = "First"),			// 第一个发现的敌人
	NEAREST		= 2		UMETA(DisplayName = "Nearest"),			// 最近的敌人
};

// -------------------------------------------- Struct -------------------------------------------

USTRUCT(BlueprintType)
struct FCampInfo
{
	GENERATED_BODY()

	// 阵营的类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECampType Type;					

	// 阵营的颜色（用于显示血量）
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;					

	// 阵营的图片显示
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath CampImage;

	// 阵营显示的文字
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CampName;

	// 显示当前阵营剩余人数时，显示的string
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LeftNumDisplay;
};

/**
 * 
 */
UCLASS()
class DEMO1_API UGeneralDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FCampInfo> CampInfoList;

	UPROPERTY(EditAnywhere)
	TArray<FSoftClassPath> SoldierInfoList;

	// UI 总配置，UI 唯一id，对应UI路径
	UPROPERTY(EditAnywhere, Category = UIConfig)
	TMap<FString, FSoftClassPath> UIMap;

	// 默认打开的UI
	UPROPERTY(EditAnywhere, Category=UIConfig)
	FString DefaultUI;

	// 血条 UI 控件
	UPROPERTY(EditAnywhere, Category=UIConfig)
	FSoftClassPath HpBar_Path;
};
