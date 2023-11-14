// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GeneralDataAsset.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneralConfig.generated.h"

UCLASS()
class DEMO1_API AGeneralConfig : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralConfig();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Init();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGeneralDataAsset* GeneralDataAsset = nullptr;
};
