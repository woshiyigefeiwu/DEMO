// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"
#include "Demo1/AIController/AIController_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacter_Base::AAICharacter_Base()
{
	//GetClass()->FindPropertyByName();


}

void AAICharacter_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateAttackState();

	
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

AAICharacter_Base* AAICharacter_Base::GetLockedEnemy()
{
	return M_LockedEnemy;
}

void AAICharacter_Base::SetLockedEnemy(AAICharacter_Base* Enemy)
{
	M_LockedEnemy = Enemy;
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

void AAICharacter_Base::UpdateAttackState()
{
	
	//if (!IsAttack())
	//{
		AAIController_Base* AIC = Cast<AAIController_Base>(GetController());

		// 检查一下当前两者之间的距离
		if (M_LockedEnemy)
		{
			float dis = FVector::Distance(GetActorLocation(), M_LockedEnemy->GetActorLocation());
			if (dis <= AttackRadius)
			{
				if (AIC)
				{
					// 不是攻击状态才需要设置
					if (AIC->GetBlackboard() && !AIC->GetBlackboard()->GetValueAsBool(FName("IsAttack")))
					{
						AIC->GetBlackboard()->SetValueAsBool(FName("IsAttack"), true);
					}
				}
			}
			else
			{
				if (AIC)
				{
					if (AIC->GetBlackboard() && AIC->GetBlackboard()->GetValueAsBool(FName("IsAttack")))
					{
						AIC->GetBlackboard()->SetValueAsBool(FName("IsAttack"), false);
					}
				}
			}
		}
		else
		{
			if (AIC)
			{
				if (AIC->GetBlackboard() && AIC->GetBlackboard()->GetValueAsBool(FName("IsAttack")))
				{
					AIC->GetBlackboard()->SetValueAsBool(FName("IsAttack"), false);
				}
			}
		}
	//}
}

ECampType AAICharacter_Base::GetCampType()
{
	return M_CampType;
}

void AAICharacter_Base::SetCampType(ECampType CampType)
{
	M_CampType = CampType;
}
