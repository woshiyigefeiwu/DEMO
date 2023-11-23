// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter_Base.h"
#include "Demo1/AIController/AIController_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Demo1/Manager/MyGameStateBase.h"
#include "Kismet/GameplayStatics.h"

AAICharacter_Base::AAICharacter_Base()
{
}

void AAICharacter_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// ----------------------------------------- Init��Get��Set��Check ���� ----------------------------------------------

// ��ʼ��һ����Ϣ
void AAICharacter_Base::Init()
{
	M_CurrentHP = MaxHP;
	M_IsDead = false;
	M_IsAttack = false;
}

ECampType AAICharacter_Base::GetCampType()
{
	return M_CampType;
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

//AAICharacter_Base* AAICharacter_Base::GetTargetEnemy()
//{
//	return M_TargetEnemy;
//}
//
//void AAICharacter_Base::SetTargetEnemy(AAICharacter_Base* NewEnemy)
//{
//	M_TargetEnemy = NewEnemy;
//}
//
//TArray<AAICharacter_Base*> AAICharacter_Base::GetEnemyArray()
//{
//	return EnemyArray;
//}

float AAICharacter_Base::GetAtk()
{
	return Atk;
}

bool AAICharacter_Base::IsInAttackCD()
{
	return GetWorldTimerManager().IsTimerActive(M_TimerHandle) == true;
}

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

float AAICharacter_Base::GetDistanceFromEnemy()
{
	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	AAICharacter_Base* TargetEnemy = AIC->GetTargetEnemy();
	if (TargetEnemy)
	{
		return FVector::Distance(this->GetActorLocation(), TargetEnemy->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("this is AAICharacter_Base::GetDistanceFromEnemy(), the M_TargetEnemy is null"));
		return INFINITY;
	}
}

//AAICharacter_Base* AAICharacter_Base::SelectTarget()
//{
//	if (EnemySelectRule == EEnemySelectRule::NONE || EnemySelectRule == EEnemySelectRule::FIRST)
//	{
//		return SelectTarget_First();
//	}
//	else if (EnemySelectRule == EEnemySelectRule::NEAREST)
//	{
//		return SelectTarget_Nearest();
//	}
//
//	return nullptr;
//}
//
//AAICharacter_Base* AAICharacter_Base::SelectTarget_First()
//{
//	AAICharacter_Base* Target = nullptr;
//
//	while (EnemyArray.Num() && (EnemyArray[0] == nullptr || EnemyArray[0]->IsDead()))
//	{
//		EnemyArray.RemoveAt(0);
//	}
//
//	if (EnemyArray.Num())
//	{
//		Target = EnemyArray[0];
//		EnemyArray.RemoveAt(0);
//	}
//	return Target;
//}

//AAICharacter_Base* AAICharacter_Base::SelectTarget_Nearest()
//{
	//USTRUCT(BlueprintType)
	//struct FTempStruct
	//{
	//	GENERATED_USTRUCT_BODY()

	//public:
	//	UPROPERTY()
	//	AAICharacter_Base* TempEnemy;

	//	UPROPERTY()
	//	float dis;		// ����֮��ľ���

	//	bool operator<(const FTempStruct& TempStructNode) const
	//	{
	//		//>�ǴӴ�С����<���Ǵ�С����
	//		return dis < TempStructNode.dis;
	//	}
	//};

	//TArray<FTempStruct> TempArray;
	//for (int i = 0; i < EnemyArray.Num(); i++)
	//{
	//	if (EnemyArray[i] != nullptr && EnemyArray[i]->IsDead() == false)
	//	{
	//		FTempStruct TempStructNode;
	//		TempStructNode.TempEnemy = EnemyArray[i];
	//		TempStructNode.dis = FVector::Distance(this->GetActorLocation(), EnemyArray[i]->GetActorLocation());
	//		TempArray.Add(TempStructNode);
	//	}
	//}
	//TempArray.Sort();

	//AAICharacter_Base* TargetEnemy = nullptr;
	//if (TempArray.Num())
	//{
	//	TargetEnemy = TempArray[0].TempEnemy;

	//	// ��ԭ������ɾ��
	//	EnemyArray.Remove(TargetEnemy);
	//}

	//return TargetEnemy;

	//return nullptr;
//}

// ---------------------------------------- AI Behavior �ӿڣ�BT ���ã� ------------------------------------------------

void AAICharacter_Base::AttackEnemy(AAICharacter_Base* Enemy)
{
}

void AAICharacter_Base::FindTarget()
{
	//// ��Ŀ����Ŀ��δ����
	//if (M_TargetEnemy && !M_TargetEnemy->IsDead())
	//{
	//	return;
	//}

	//M_TargetEnemy = SelectTarget();

	// ��һ���¼���ȥ��AIC �ӵ�֮���޸ĺڰ�ֵ��
	//OnFindTargetFinish.Broadcast();

	// -------------------- ��д --------------------------

	AAIController_Base* AIC = Cast<AAIController_Base>(GetController());
	AIC->FindTarget();
	//if (AIC && AIC->CheckTargetEnemy())
	//{

	//}
}

void AAICharacter_Base::AI_ApplyDamage(AAICharacter_Base* Enemy)
{
	if (Enemy && GetDistanceFromEnemy() <= AttackRadius)
	{
		UGameplayStatics::ApplyDamage(Enemy, Atk, GetController(), this, TSubclassOf<UDamageType>(UDamageType::StaticClass()));
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is TryApplyDamage() succeed !!!��CloseCombat��");
	}
}
