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
		M_Blackboard->SetValueAsObject(FName("Target"), AI->GetTargetEnemy());
	}
}

// --------------------------------------------- Event ---------------------------------------

// AI �ҵ� Target ֮�󣬸���һ�ºڰ��ֵ
void AAIController_Base::FinishFindTarget()
{	
	UpdateBBV_Target();

	// ���� IsPerception���Ա� AI ����Ѳ��
	M_Blackboard->SetValueAsBool("IsPerception", false);
}
