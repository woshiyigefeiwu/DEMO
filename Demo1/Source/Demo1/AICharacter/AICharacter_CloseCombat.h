// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AICharacter_Base.h"
#include "AICharacter_CloseCombat.generated.h"

/**
 * 
 */
UCLASS()
class DEMO1_API AAICharacter_CloseCombat : public AAICharacter_Base
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	// ·¢Æð¹¥»÷
	void AttackEnemy(AAICharacter_Base* Enemy) override;
};
