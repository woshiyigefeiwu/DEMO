// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/Manager/MyGamestateBase.h"

AAIController_Base::AAIController_Base()
{
	M_BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("MyTree");
	M_Blackboard = CreateDefaultSubobject<UBlackboardComponent>("MyBoard");
}

void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAIBehaviorTree(InPawn);
}

void AAIController_Base::BeginPlay()
{
	Super::BeginPlay();
}

// ---------------------------------- Init，Get，Set，Check 函数 --------------------------------------

UBlackboardComponent* AAIController_Base::GetBlackboard()
{
	return M_Blackboard;
}

void AAIController_Base::InitBlackboardValue()
{
	M_IsInAttackRange = false;
}

bool AAIController_Base::Get_IsInAttackRange()
{
	return M_IsInAttackRange;
}

void AAIController_Base::Set_IsInAttackRange(bool State)
{
	M_IsInAttackRange = State;
}

AAICharacter_Base* AAIController_Base::GetTargetEnemy()
{
	return M_TargetEnemy;
}

void AAIController_Base::SetTargetEnemy(AAICharacter_Base* NewEnemy)
{
	M_TargetEnemy = NewEnemy;
}

TArray<AAICharacter_Base*> AAIController_Base::GetEnemyArray()
{
	return M_EnemyArray;
}

// -------------------------------------------- 辅助函数 -----------------------------------

void AAIController_Base::RunAIBehaviorTree(APawn* InPawn)
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(InPawn);
	if (AI && AI->GetBTree())
	{
		M_Blackboard->InitializeBlackboard(*AI->GetBTree()->BlackboardAsset);		// 初始化AI中的黑板，黑板是在行为树中的。
		M_BehaviorTree->StartTree(*AI->GetBTree());									// 开始运行行为树
	}
}

void AAIController_Base::UpdateBBV_IsInAttackRange()
{
	M_Blackboard->SetValueAsBool("IsInAttackRange", M_IsInAttackRange);
}

void AAIController_Base::UpdateBBV_Target()
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(GetPawn());
	if (AI)
	{
		M_Blackboard->SetValueAsObject(FName("Target"), M_TargetEnemy);
	}
}

float AAIController_Base::GetDistanceFromEnemy()
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(GetPawn());
	if (AI && M_TargetEnemy)
	{
		return FVector::Distance(AI->GetActorLocation(), M_TargetEnemy->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("this is AAICharacter_Base::GetDistanceFromEnemy(), the M_TargetEnemy is null"));
		return INFINITY;
	}
}

AAICharacter_Base* AAIController_Base::SelectTarget()
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(GetPawn());
	EEnemySelectRule EnemySelectRule = AI->EnemySelectRule;

	if (EnemySelectRule == EEnemySelectRule::NONE || EnemySelectRule == EEnemySelectRule::FIRST)
	{
		return SelectTarget_First();
	}
	else if (EnemySelectRule == EEnemySelectRule::NEAREST)
	{
		return SelectTarget_Nearest();
	}

	return nullptr;
}

AAICharacter_Base* AAIController_Base::SelectTarget_First()
{
	AAICharacter_Base* Target = nullptr;

	while (M_EnemyArray.Num() && (M_EnemyArray[0] == nullptr || M_EnemyArray[0]->IsDead()))
	{
		M_EnemyArray.RemoveAt(0);
	}

	if (M_EnemyArray.Num())
	{
		Target = M_EnemyArray[0];
		M_EnemyArray.RemoveAt(0);
	}
	return Target;
}

AAICharacter_Base* AAIController_Base::SelectTarget_Nearest()
{
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

	return nullptr;
}

// 处理 AI 死亡
void AAIController_Base::AIDead()
{
	// 目前只有停止行为树
	M_BehaviorTree->StopLogic("AIDead");
}
