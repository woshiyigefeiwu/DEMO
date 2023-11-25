// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/Color.h"

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneralDataAsset.generated.h"

// -------------------------------------------- Enum -------------------------------------------

// ��Ӫ
UENUM(BlueprintType)
enum class ECampType : uint8
{
	NONE,
	RED		=	1	UMETA(DisplayName = "Red"),
	BLUE	=	2	UMETA(DisplayName = "Blue"),
};

// ����
UENUM(BlueprintType)
enum class ESoldierType : uint8
{
	NONE,
	CLOSECOMBAT		= 1		UMETA(DisplayName = "CloseCombat"),
	LONGRANGE		= 2		UMETA(DisplayName = "LongRange"),
};

// ѡ�й���
UENUM(BlueprintType)
enum class EEnemySelectRule : uint8
{
	NONE,
	FIRST		= 1		UMETA(DisplayName = "First"),			// ��һ�����ֵĵ���
	NEAREST		= 2		UMETA(DisplayName = "Nearest"),			// ����ĵ���
};

// -------------------------------------------- Struct -------------------------------------------

USTRUCT(BlueprintType)
struct FCampInfo
{
	GENERATED_BODY()

	// ��Ӫ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECampType Type;					

	// ��Ӫ����ɫ��������ʾѪ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;					

	// ��Ӫ��ͼƬ��ʾ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath CampImage;

	// ��Ӫ��ʾ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CampName;

	// ��ʾ��ǰ��Ӫʣ������ʱ����ʾ��string
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

	// UI �����ã�UI Ψһid����ӦUI·��
	UPROPERTY(EditAnywhere, Category = UIConfig)
	TMap<FString, FSoftClassPath> UIMap;

	// Ĭ�ϴ򿪵�UI
	UPROPERTY(EditAnywhere, Category=UIConfig)
	FString DefaultUI;

	// Ѫ�� UI �ؼ�
	UPROPERTY(EditAnywhere, Category=UIConfig)
	FSoftClassPath HpBar_Path;
};
