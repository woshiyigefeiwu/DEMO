// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	UFUNCTION()
	void BeginPlay() override;

	UFUNCTION()
	void Init();

	// ------------------------------------------ spawn AI -----------------------------------------

	UFUNCTION(BlueprintCallable)
	void SpawnAI(FSoftClassPath SoftClassPath, FVector MouseLocation);

	UFUNCTION()
	UClass* LoadAIClass(FSoftClassPath SoftClassPath);

	// ------------------------------------------ other --------------------------------------------

	//UFUNCTION()
	//void HideMouse();

private:
	//UPROPERTY()
	//FTimerHandle M_TimerHandle;
};
