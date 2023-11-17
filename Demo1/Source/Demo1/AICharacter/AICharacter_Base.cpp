// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"
#include "Demo1/AIController/AIController_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacter_Base::AAICharacter_Base()
{

}

void AAICharacter_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

// 初始化一下信息
void AAICharacter_Base::Init()
{
	M_CurrentHP = MaxHP;
}

ESoldierType AAICharacter_Base::GetSoldierType()
{
	return SoldierType;
}

UBehaviorTree* AAICharacter_Base::GetBTree()
{
	return BTree;
}

void AAICharacter_Base::UpdateWalkSpeed()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = MoveSpeed;
}

// 是否在攻击状态
bool AAICharacter_Base::IsAttack()
{
	bool is_attack = false;
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	if (AIC)
	{
		if (AIC->GetBlackboard())
		{
			is_attack = AIC->GetBlackboard()->GetValueAsBool(FName("IsAttack"));
		}
	}

	return is_attack;
}

bool AAICharacter_Base::IsDead()
{
	return M_IsDead;
}

void AAICharacter_Base::SetDeadState(bool DeadState)
{
	M_IsDead = DeadState;
}

float AAICharacter_Base::SetCurrentHP(float NewHP)
{
	M_CurrentHP = NewHP;
	return M_CurrentHP;
}

ECampType AAICharacter_Base::GetCampType()
{
	return M_CampType;
}

void AAICharacter_Base::SetCampType(ECampType CampType)
{
	M_CampType = CampType;
}
