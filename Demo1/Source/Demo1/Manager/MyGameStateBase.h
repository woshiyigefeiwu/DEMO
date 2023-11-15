// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralDataAsset.h"
#include "Demo1/AICharacter/AICharacter_Base.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"


// ��ǰ��Ӫ����ǰ�����µ�����AI
USTRUCT(BlueprintType)
struct FCamp_Solider_AIList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int Num;		// ����

	UPROPERTY()
	TArray<AAICharacter_Base*> Camp_Solider_AIList;
};

// ��ǰ��Ӫ �����е� AI
USTRUCT(BlueprintType)
struct FCamp_AIList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int Num;		// ����

	UPROPERTY()
	TMap<ESoldierType, FCamp_Solider_AIList> Camp_AIList;
};

/**
 * 
 */
UCLASS()
class DEMO1_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void BeginPlay() override;
	
	UFUNCTION()
	void Init();

	UFUNCTION()
	TArray<FCampInfo> GetCampInfoList();

	UFUNCTION()
	TArray<FSoftClassPath> GetSoldierInfoList();

	UFUNCTION(BlueprintCallable)
	void SetCurrentCamp(ECampType CurrentCamp);

	UFUNCTION()
	ECampType GetCurrentCamp();

	UFUNCTION()
	void AddAI(AAICharacter_Base* AI);

private:
	UPROPERTY(EditAnywhere)
	TArray<FCampInfo> M_CampInfoList;

	UPROPERTY(EditAnywhere)
	TArray<FSoftClassPath> M_SoldierInfoList;

	// ��ǰѡ�����Ӫ
	UPROPERTY()
	ECampType M_CurrentCamp;

	// ����Ϸ������������ݣ�ÿ����Ӫ����ÿ�����֣��� AI �Լ�������
	UPROPERTY()
	TMap<ECampType, FCamp_AIList> M_AIList;
};


//UPROPERTY(EditAnywhere)
//TArray<FSoldierInfo> M_SoldierInfoList;