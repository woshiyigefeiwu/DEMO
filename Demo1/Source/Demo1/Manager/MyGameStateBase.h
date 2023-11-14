// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	void BeginPlay() override;
	
	UFUNCTION()
	void Init();

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
