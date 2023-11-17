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
	if (SelectRule == EEnemySelectRule::FIRST || SelectRule == EEnemySelectRule::NONE)
	{
		return this->SelectTarget_First(AI_Array);
	}
	else if (SelectRule == EEnemySelectRule::NEAREST)
	{
		return this->SelectTarget_Nearest(AI_Array);
	}

	return nullptr;
}

// �ҵ�һ�����ֵĵ��ˣ��Ϸ��ģ�
AAICharacter_Base* AAIController_Base::SelectTarget_First(TArray<AAICharacter_Base*> AI_Array)
{
	AAICharacter_Base* Target = nullptr;

	while (AI_Array.Num() && (AI_Array[0] == nullptr || AI_Array[0]->IsDead()))
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

UBlackboardComponent* AAIController_Base::GetBlackboard()
{
	return M_Blackboard;
}

// ��Ҫ��һЩ���ݵĴ���
void AAIController_Base::PossessAIDead()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, "this is PossessAIDead(), DataUpdate");

	AAICharacter_Base* AI = Cast<AAICharacter_Base>(GetPawn());
	AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
	
	if (GS)
	{
		GS->DeleteAI(AI);
	}
}

// AI ��ɹ���֮����ƺ���
void AAIController_Base::FinishAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, "this is AAIController_CloseCombat::FinishAttack()");

	AAICharacter_Base* PossessAI = Cast<AAICharacter_Base>(GetPawn());
	if (PossessAI)
	{
		GetWorldTimerManager().SetTimer(M_TimerHandle, this, &AAIController_Base::ClearTimerHandle, PossessAI->AtkCD, false);
	}
}

// ��ն�ʱ��
void AAIController_Base::ClearTimerHandle()
{
	GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Yellow, "this is AAIController_CloseCombat::ClearTimerHandle()");

	GetWorldTimerManager().ClearTimer(M_TimerHandle);
}