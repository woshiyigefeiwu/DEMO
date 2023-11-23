// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_CloseCombat.h"
#include "Demo1/AIController/AIController_CloseCombat.h"

void AAICharacter_CloseCombat::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter_CloseCombat::AttackEnemy(AAICharacter_Base* Enemy)
{
	UE_LOG(LogTemp, Error, TEXT("this is AAICharacter_CloseCombat::AttackEnemy()"));

	// À¶Í¼ÄÇ±ß°ó¶¨£¬¿ªÊ¼²¥¹¥»÷¶¯»­
	OnLaunchAttack.Broadcast();
}

