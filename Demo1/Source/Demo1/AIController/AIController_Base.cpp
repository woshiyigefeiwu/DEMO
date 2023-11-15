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
		M_Blackboard->InitializeBlackboard(*AI->GetBTree()->BlackboardAsset);		// ��ʼ��AI�еĺڰ壬�ڰ�������Ϊ���еġ�
		M_BehaviorTree->StartTree(*AI->GetBTree());								//��ʼ������Ϊ��
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

// �ҵ�һ�����ֵĵ���
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

// �Ҿ�������ĵ���
AAICharacter_Base* AAIController_Base::SelectTarget_Nearest(TArray<AAICharacter_Base*> AI_Array)
{
	// ����ô���һ��

	// ��һ�����еĵ��˵�ָ�� -> ��ȡλ�� -> ��һ�µ� this �ľ��룬Ȼ�������һ�������dis��AIi����Ȼ������Ȼ��ȡ��������ԭ������ɾ����

	return nullptr;
}
