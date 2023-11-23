// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"
#include "Demo1/AIController/AIController_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Demo1/Manager/MyGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Demo1/Manager/MyGameModeBase.h"

AAICharacter_Base::AAICharacter_Base()
{
}

void AAICharacter_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAICharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	AfterOnPossessed();
}

// ----------------------------------------- Init，Get，Set，Check 函数 ----------------------------------------------

// 初始化一下信息
void AAICharacter_Base::Init()
{
	M_CurrentHP = MaxHP;
	M_IsDead = false;
	M_IsAttack = false;
}

void AAICharacter_Base::AfterOnPossessed()
{
	OnAfterPossessed.Broadcast();
}

ECampType AAICharacter_Base::GetCampType()
{
	return M_CampType;
}

FColor AAICharacter_Base::GetColorByCampType()
{
	const AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->GeneralDataAsset)
	{
		for (int i = 0; i < GM->GeneralDataAsset->CampInfoList.Num(); i++)
		{
			if (GM->GeneralDataAsset->CampInfoList[i].Type == M_CampType)
			{
				return GM->GeneralDataAsset->CampInfoList[i].Color;
			}
		}
	}
	
	return FColor();
}

void AAICharacter_Base::SetCampType(ECampType CampType)
{
	M_CampType = CampType;
}

ESoldierType AAICharacter_Base::GetSoldierType()
{
	return SoldierType;
}

UBehaviorTree* AAICharacter_Base::GetBTree()
{
	return BTree;
}

// 是否在攻击状态
bool AAICharacter_Base::IsAttack()
{
	return M_IsAttack;
}

bool AAICharacter_Base::IsDead()
{
	return M_IsDead;
}

float AAICharacter_Base::SetCurrentHP(float NewHP)
{
	M_CurrentHP = NewHP;
	return M_CurrentHP;
}

float AAICharacter_Base::GetAtk()
{
	return Atk;
}

bool AAICharacter_Base::IsInAttackCD()
{
	return GetWorldTimerManager().IsTimerActive(M_TimerHandle) == true;
}

// ------------------------------------------- 辅助函数 -----------------------------------

void AAICharacter_Base::UpdateWalkSpeed()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = MoveSpeed;
}

float AAICharacter_Base::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("this is TakeDamage(), the Damage is %f"), DamageTaken));

	float CurrentHP = M_CurrentHP;
	if (CurrentHP > 0)
	{
		CurrentHP = SetCurrentHP(M_CurrentHP - DamageTaken);
	}

	if (CurrentHP <= 0)
	{
		AIDead();
	}

	OnTakeDamage.Broadcast();

	return CurrentHP;
}

void AAICharacter_Base::AIDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is AIDead()");

	M_IsDead = false;

	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	if (GS)
	{
		GS->DeleteAI(this);
	}

	// 销毁（可能得抛个事件出去，然后拨个动画之类的）
	Destroyed();
}

void AAICharacter_Base::EntryAttackCD()
{
	GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Yellow, "AAICharacter_Base::EntryAttackCD");

	GetWorldTimerManager().SetTimer(M_TimerHandle, this, &AAICharacter_Base::ClearTimerHandle, AtkCD, false);
}

void AAICharacter_Base::ClearTimerHandle()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, "this is AAICharacter_Base::ClearTimerHandle()");

	GetWorldTimerManager().ClearTimer(M_TimerHandle);
}

// ---------------------------------------- AI Behavior 接口（BT 调用） ------------------------------------------------

void AAICharacter_Base::AttackEnemy(AAICharacter_Base* Enemy)
{
}

void AAICharacter_Base::FindTarget()
{
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	AIC->FindTarget();
}

void AAICharacter_Base::AI_ApplyDamage(AAICharacter_Base* Enemy)
{
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	if (AIC) 
	{
		if (Enemy && AIC->GetDistanceFromEnemy() <= AttackRadius)
		{
			UGameplayStatics::ApplyDamage(Enemy, Atk, AIC, this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is TryApplyDamage() succeed !!!（CloseCombat）");
		}
	}
}
