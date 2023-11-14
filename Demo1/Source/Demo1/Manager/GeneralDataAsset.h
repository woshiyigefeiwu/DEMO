// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/Color.h"

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GeneralDataAsset.generated.h"


// ��Ӫ
UENUM(BlueprintType)
enum class ECampType : uint8
{
	NONE,
	RED		=	1	UMETA(DisplayName = "Red"),
	BLUE	=	2	UMETA(DisplayName = "Blue"),
};


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
};

// ����
UENUM(BlueprintType)
enum class ESoldierType : uint8
{
	NONE,
	CLOSECOMBAT = 1		UMETA(DisplayName = "CloseCombat"),
	LONGRANGE = 2		UMETA(DisplayName = "LongRange"),
};

USTRUCT(BlueprintType)
struct FSoldierInfo
{
	GENERATED_BODY()

	// ʿ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESoldierType Type;					

	// ʿ������ͼ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftClassPath SoldierClass;		

	// ʿ����ͼƬ��ʾ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSoftObjectPath SoldierImage;
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
	TArray<FSoldierInfo> SoldierInfoList;

	// ��Ϸ��ʼ����
	UPROPERTY(EditAnywhere)
	FSoftClassPath WBP_GameStart;

	// ѡ����Ӫ����
	UPROPERTY(EditAnywhere)
	FSoftClassPath WBP_SelectCamp;

	// ���ý���
	UPROPERTY(EditAnywhere)
	FSoftClassPath WBP_PlaceAI;

	// ��Ϸ����ʱ����
	UPROPERTY(EditAnywhere)
	FSoftClassPath WBP_GamePlay;
};
