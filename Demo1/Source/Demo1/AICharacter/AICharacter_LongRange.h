// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter_Base.h"
#include "AICharacter_LongRange.generated.h"


/**
 * 
 */
UCLASS()
class DEMO1_API AAICharacter_LongRange : public AAICharacter_Base
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	// 发起攻击
	void AttackEnemy(AAICharacter_Base* Enemy) override;

	// 开火
	UFUNCTION()
	void StartFire();

public:
	// 发射物
	UPROPERTY(EditAnywhere, Category = "SpecialConfig")
	FSoftClassPath ProjectileClass;
};
