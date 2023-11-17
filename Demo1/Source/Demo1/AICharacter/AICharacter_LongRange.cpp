// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_LongRange.h"
#include "Demo1/AIController/AIController_Base.h"

void AAICharacter_LongRange::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter_LongRange::AttackEnemy()
{
	UE_LOG(LogTemp, Error, TEXT("this is AttackEnemy(), AI Attack"));

	AttackDelegate.Broadcast();

	// 创建发射物，发射就行



	// 发起一次攻击之后，交给 AIController 做善后处理
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	AIC->FinishAttack();
}

float AAICharacter_LongRange::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Error, TEXT("this is TakeDamage(), the Damage is %f"), DamageTaken);
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("this is TakeDamage(), the Damage is %f"), DamageTaken));

	float CurrentHP = M_CurrentHP;
	if (CurrentHP > 0)
	{
		CurrentHP = SetCurrentHP(M_CurrentHP - DamageTaken);
	}
	
	if (CurrentHP <= 0)
	{
		Death();

		AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
		AIC->PossessAIDead();
	}

	return CurrentHP;
}

void AAICharacter_LongRange::Death()
{
	// UE_LOG(LogTemp, Error, TEXT("this is Death(), AI Death"));
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("this is Death(), I am dead")));

	M_IsDead = true;
}


