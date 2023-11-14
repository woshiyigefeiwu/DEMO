// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralConfig.h"
#include "GeneralDataAsset.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION()
	void CreateGeneralConfig();

	UFUNCTION()
	AGeneralConfig* GetGeneralConfig();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataAssets")
	UGeneralDataAsset* GeneralDataAsset = nullptr;

private:
	AGeneralConfig* M_GeneralConfig = nullptr;
};
