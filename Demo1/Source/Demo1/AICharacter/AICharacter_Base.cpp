// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"
#include "Demo1/AIController/AIController_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Demo1/Manager/MyGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Components//WidgetComponent.h"

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

// ----------------------------------------- Init��Get��Set��Check ���� ----------------------------------------------

// ��ʼ��һ����Ϣ
void AAICharacter_Base::Init()
{
	M_CurrentHP = MaxHP;
	M_IsDead = false;
	M_IsAttack = false;

	// ��Ӫ��Ϣ
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

// �Ƿ��ڹ���״̬
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

//void AAICharacter_Base::InitHpUI()
//{
	//// ��ʼ��һ�� UI
	//const AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	//if (GM && GM->GeneralDataAsset)
	//{
	//	FString HpBarPath = "Blueprint'";
	//	HpBarPath.Append(GM->GeneralDataAsset->HpBar_Path.ToString());
	//	HpBarPath.Append("'");

	//	UClass* HpBarClass = LoadClass<UUserWidget>(NULL, *HpBarPath);
	//	WidgetComponent->SetWidgetClass(HpBarClass);
	//}

	//WidgetComponent->GetWidget();
//}

// ------------------------------------------- �������� -----------------------------------

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
	//RefreshHpUI();

	return CurrentHP;
}

void AAICharacter_Base::AIDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is AIDead()");

	M_IsDead = true;

	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	if (GS)
	{
		GS->DeleteAI(this);
	}

	// �׸��¼���ȥ��Ȼ�󲦸�����֮��ģ���������AI��
	OnAIDead.Broadcast();

	// ���� AIC ȥ�����߼���ֹͣ��Ϊ����
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	if (AIC)
	{
		AIC->AIDead();
	}

	//Destroy();
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

// ---------------------------------------- AI Behavior �ӿڣ�BT ���ã� ------------------------------------------------

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
			GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is TryApplyDamage() succeed !!!��CloseCombat��");
		}
	}
}
