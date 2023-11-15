// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"

AAICharacter_Base::AAICharacter_Base()
{
	//GetClass()->FindPropertyByName();


}

ESoldierType AAICharacter_Base::GetSoldierType()
{
	return SoldierType;
}

UBehaviorTree* AAICharacter_Base::GetBTree()
{
	return BTree;
}

void AAICharacter_Base::UpdateWalkSpeed(float Speed)
{
	CharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = Speed;
}

ECampType AAICharacter_Base::GetCampType()
{
	return M_CampType;
}

void AAICharacter_Base::SetCampType(ECampType CampType)
{
	M_CampType = CampType;
}
