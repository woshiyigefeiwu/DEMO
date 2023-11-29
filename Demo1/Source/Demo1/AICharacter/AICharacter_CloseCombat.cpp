// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_CloseCombat.h"
#include "Demo1/AIController/AIController_CloseCombat.h"

void AAICharacter_CloseCombat::BeginPlay()
{
	Super::BeginPlay();
}

void AAICharacter_CloseCombat::AttackEnemy(AAICharacter_Base* Enemy)
{
	//UE_LOG(LogTemp, Error, TEXT("this is AAICharacter_CloseCombat::AttackEnemy()"));

	// À¶Í¼ÄÇ±ß°ó¶¨£¬¿ªÊ¼²¥¹¥»÷¶¯»­
	OnLaunchAttack.Broadcast();
}

//float AAICharacter_CloseCombat::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
//{
//	Super::TakeDamage(DamageTaken, DamageEvent, EventInstigator, DamageCauser);
//
//	//FString SkillId = "Skill_AddAtk_01";
//	//if (CanExecuteSkill(SkillId))
//	//{
//	//	ReduceSkillConsume(SkillId);
//	//	ExecuteSkill(SkillId);
//	//}
//
//	return 0.0f;
//}

