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
	UFUNCTION()
	void AttackEnemy();

	// 受到攻击（从APawn覆盖）
	UFUNCTION()
	float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// 死亡接口
	UFUNCTION()
	void Death();

public:

};
