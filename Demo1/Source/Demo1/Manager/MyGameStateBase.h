// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralDataAsset.h"
#include "GeneralConfig.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Init(UGeneralDataAsset* GeneralDataAsset);

	UFUNCTION()
	void PostInitializeComponents() override;

	UFUNCTION()
	TArray<FCampInfo> GetCampInfoList();

	UFUNCTION()
	TArray<FSoldierInfo> GetSoldierInfoList();

private:
	UPROPERTY(EditAnywhere)
	TArray<FCampInfo> M_CampInfoList;

	UPROPERTY(EditAnywhere)
	TArray<FSoldierInfo> M_SoldierInfoList;
};
