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

	BindDelegateFromAI(InPawn);

	RunAIBehaviorTree(InPawn);
}

void AAIController_Base::BeginPlay()
{
	Super::BeginPlay();
}

// ---------------------------------- Init��Get��Set��Check ���� --------------------------------------

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

// -------------------------------------------- �������� -----------------------------------

void AAIController_Base::RunAIBehaviorTree(APawn* InPawn)
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(InPawn);
	if (AI && AI->GetBTree())
	{
		M_Blackboard->InitializeBlackboard(*AI->GetBTree()->BlackboardAsset);		// ��ʼ��AI�еĺڰ壬�ڰ�������Ϊ���еġ�
		M_BehaviorTree->StartTree(*AI->GetBTree());									// ��ʼ������Ϊ��
	}
}

void AAIController_Base::BindDelegateFromAI(APawn* InPawn)
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(InPawn);
	if (AI)
	{
		AI->OnFindTargetFinish.AddDynamic(this, &AAIController_Base::FinishFindTarget);
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
	return nullptr;
}

// --------------------------------------------- Event ---------------------------------------

// AI �ҵ� Target ֮�󣬸���һ�ºڰ��ֵ
void AAIController_Base::FinishFindTarget()
{	
	UpdateBBV_Target();

	// ���� IsPerception���Ա� AI ����Ѳ��
	M_Blackboard->SetValueAsBool("IsPerception", false);
}
