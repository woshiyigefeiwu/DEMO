// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralConfig.h"

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

	UFUNCTION()
	void BeginPlay() override;
};
