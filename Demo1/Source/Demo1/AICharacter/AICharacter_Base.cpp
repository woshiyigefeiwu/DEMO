// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"
#include "Demo1/AIController/AIController_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Demo1/Manager/MyGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Components/WidgetComponent.h"
#include "Demo1/Skill/SkillComponent.h"
#include "Demo1/Skill/SkillConfig.h"

AAICharacter_Base::AAICharacter_Base()
{
	//WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	//WidgetComponent->SetupAttachment(RootComponent);
}

void AAICharacter_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAICharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	
	Init_BP();
}

// ----------------------------------------- Init，Get，Set，Check 函数 ----------------------------------------------

// 初始化一下信息
void AAICharacter_Base::Init()
{
	M_CurrentHP = MaxHP;
	M_IsDead = false;
	M_IsAttack = false;

	// 阵营信息
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	if (GS)
	{
		SetCampType(GS->GetCurrentCamp());
	}
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
	OnChangeHp.Broadcast();
	return M_CurrentHP;
}

FString AAICharacter_Base::GetImagePath()
{
	return ShowImage.ToString();
}

float AAICharacter_Base::GetAtk()
{
	return Atk;
}

bool AAICharacter_Base::IsInAttackCD()
{
	return GetWorldTimerManager().IsTimerActive(M_TimerHandle) == true;
}

void AAICharacter_Base::TryExecuteSkillWhenHp()
{
	if (SkillComponent)
	{
		SkillComponent->TryExecuteSkillWhenHp();
	}
}

bool AAICharacter_Base::IsCanApplyDamage(AActor* Target)
{
	// 能转换 且 不同阵营 才能 施加伤害
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(Target);
	if(AI && AI->GetCampType() != this->GetCampType())
	{
		return true;
	}
	
	return false;
}

void AAICharacter_Base::ApplyDamageToAI(AActor* Target)
{
	AAICharacter_Base* AITarget = Cast<AAICharacter_Base>(Target);
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	if (AITarget && AIC)
	{
		UGameplayStatics::ApplyDamage(AITarget, GetTotalAtk(), AIC, this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
	}
}

void AAICharacter_Base::SetSkillComponent(USkillComponent* NewSkillComponent)
{
	SkillComponent = NewSkillComponent;
}
// ------------------------------------------- 辅助函数 -----------------------------------

void AAICharacter_Base::UpdateWalkSpeed()
{
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = MoveSpeed;
}

float AAICharacter_Base::TakeDamage(float DamageTaken, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("this is TakeDamage(), the Damage is %f"), DamageTaken));

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

	// 尝试触发所有触发条件为扣血的技能
	TryExecuteSkillWhenHp();

	return CurrentHP;
}

void AAICharacter_Base::AIDead()
{
	//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is AIDead()");

	M_IsDead = true;

	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	if (GS)
	{
		GS->DeleteAI(this);
	}

	// 抛个事件出去，然后拨个动画之类的（播完销毁AI）
	OnAIDead.Broadcast();

	// 交给 AIC 去处理逻辑（停止行为树）
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	if (AIC)
	{
		AIC->AIDead();
	}

	//Destroy();
}

void AAICharacter_Base::EntryAttackCD()
{
	//GEngine->AddOnScreenDebugMessage(-1, 300, FColor::Yellow, "AAICharacter_Base::EntryAttackCD");

	GetWorldTimerManager().SetTimer(M_TimerHandle, this, &AAICharacter_Base::ClearTimerHandle, AtkCD, false);
}

void AAICharacter_Base::ClearTimerHandle()
{
	//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, "this is AAICharacter_Base::ClearTimerHandle()");

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

// -------------------------------------- Skill ------------------------------------

bool AAICharacter_Base::RunExecuteSkill(FString SkillId)
{
	if (SkillComponent)
	{
		return SkillComponent->RunExecuteSkill(SkillId);
	}

	return false;
}

//bool AAICharacter_Base::CanExecuteSkill(FString SkillId)
//{
//	if (SkillComponent)
//	{
//		return SkillComponent->CanExecuteSkill(SkillId);
//	}
//
//	return false;
//}
//
//void AAICharacter_Base::ReduceSkillConsume(FString SkillId)
//{
//	if (SkillComponent)
//	{
//		return SkillComponent->ReduceSkillConsume(SkillId);
//	}
//}
//
//void AAICharacter_Base::ExecuteSkill(FString SkillId)
//{
//	if (SkillComponent)
//	{
//		return SkillComponent->ExecuteSkill(SkillId);
//	}
//}

float AAICharacter_Base::GetTotalCurrentHp()
{
	float TotalCurrentHp = M_CurrentHP;
	if (SkillComponent)
	{
		//TotalCurrentHp += SkillComponent->GetTotalAttachHp();
		TotalCurrentHp += SkillComponent->GetTotalSkillAttributeValueByEAttributeType(EAttributeType::AttachHP);
	}

	return TotalCurrentHp;
}

float AAICharacter_Base::GetTotalAtk()
{
	float TotalAtk = Atk;
	if (SkillComponent)
	{
		//TotalAtk += SkillComponent->GetTotalAttachAtk();
		TotalAtk += SkillComponent->GetTotalSkillAttributeValueByEAttributeType(EAttributeType::AttachATK);
	}

	return TotalAtk;
}