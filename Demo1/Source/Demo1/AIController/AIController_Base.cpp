// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Demo1/AICharacter/AICharacter_Base.h"

AAIController_Base::AAIController_Base()
{
	M_BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("MyTree");
	M_Blackboard = CreateDefaultSubobject<UBlackboardComponent>("MyBoard");
}

void AAIController_Base::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAICharacter_Base* AI = Cast<AAICharacter_Base>(InPawn);
	if (AI && AI->GetBTree())
	{
		M_Blackboard->InitializeBlackboard(*AI->GetBTree()->BlackboardAsset);		// 初始化AI中的黑板，黑板是在行为树中的。
		M_BehaviorTree->StartTree(*AI->GetBTree());								//开始运行行为树
	}
}

void AAIController_Base::BeginPlay()
{
	Super::BeginPlay();
}

AAICharacter_Base* AAIController_Base::SelectTarget(EEnemySelectRule SelectRule, TArray<AAICharacter_Base*> AI_Array)
{
	if (SelectRule == EEnemySelectRule::FIRST)
	{
		return this->SelectTarget_First(AI_Array);
	}
	else if (SelectRule == EEnemySelectRule::NEAREST)
	{
		return this->SelectTarget_Nearest(AI_Array);
	}

	return nullptr;
}

// 找第一个发现的敌人
AAICharacter_Base* AAIController_Base::SelectTarget_First(TArray<AAICharacter_Base*> AI_Array)
{
	AAICharacter_Base* Target = nullptr;

	while (AI_Array.Num() && AI_Array[0] == nullptr)
	{
		AI_Array.RemoveAt(0);
	}

	if (AI_Array.Num())
	{
		Target = AI_Array[0];
		AI_Array.RemoveAt(0);
	}
	return Target;
}

// 找距离最近的敌人
AAICharacter_Base* AAIController_Base::SelectTarget_Nearest(TArray<AAICharacter_Base*> AI_Array)
{
	// 这里得处理一下

	// 找一下所有的敌人的指针 -> 获取位置 -> 算一下到 this 的距离，然后存在另一个数组里（dis，AIi），然后排序，然后取出来，在原数组中删除。

	return nullptr;
}
