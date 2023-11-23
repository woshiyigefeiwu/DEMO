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

// ----------------------------------------- Init，Get，Set，Check 函数 ----------------------------------------------

// 初始化一下信息
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
	//	float dis;		// 两者之间的距离

	//	bool operator<(const FTempStruct& TempStructNode) const
	//	{
	//		//>是从大到小排序，<就是从小到大
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

	//	// 从原数组中删除
	//	EnemyArray.Remove(TargetEnemy);
	//}

	//return TargetEnemy;

	//return nullptr;
//}

// ---------------------------------------- AI Behavior 接口（BT 调用） ------------------------------------------------

void AAICharacter_Base::AttackEnemy(AAICharacter_Base* Enemy)
{
}

void AAICharacter_Base::FindTarget()
{
	//// 有目标且目标未死亡
	//if (M_TargetEnemy && !M_TargetEnemy->IsDead())
	//{
	//	return;
	//}

	//M_TargetEnemy = SelectTarget();

	// 抛一个事件出去，AIC 接到之后，修改黑板值。
	//OnFindTargetFinish.Broadcast();

	// -------------------- 重写 --------------------------

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
		GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is TryApplyDamage() succeed !!!（CloseCombat）");
	}
}
