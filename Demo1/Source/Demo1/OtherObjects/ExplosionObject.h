// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionObject.generated.h"

class AAICharacter_Base;
class UStaticMeshComponent;

UCLASS()
class DEMO1_API AExplosionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void Init(AAICharacter_Base* AI, FVector ExplosionRange, float ExplosionTime);

public:
	//float AfterExplosionTime;

	//float LastTime;

	//AAICharacter_Base* OwnerAI = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	//UStaticMeshComponent* StaticMesh = nullptr;

};
