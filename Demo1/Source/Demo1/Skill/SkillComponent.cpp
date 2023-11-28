// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "Demo1/Manager/SkillManager.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Skill_Base.h"
#include "Demo1/AICharacter/AICharacter_Base.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// 双向绑定一下
	MyOwner = GetOwner();
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(MyOwner);
	AI->SetSkillComponent(this);

	// 创建技能
	CreateSkill();
}

// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::CreateSkill()
{
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(MyOwner));
	if (GM && GM->GetSkillManager())
	{
		ASkillManager* SkillManager = GM->GetSkillManager();

		for (TMap<ESkillType, FArrayString_Node>::TConstIterator iter = SkillConfig.CreateConstIterator(); iter; ++iter)
		{
			ASkill_Base* Skill = SkillManager->CreateSkill(iter->Key);
			if (Skill)
			{
				Skill->Init(this, iter->Key);
				Skills.Add(iter->Key, Skill);
			}
		}
	}
}

void USkillComponent::ExecuteSkill(ESkillType SkillType)
{
	if (SkillConfig.Contains(SkillType) && Skills.Contains(SkillType))
	{
		ASkill_Base* Skill = Skills[SkillType];
		TArray<FString> SkillIdList = SkillConfig[SkillType].Array;
		for (int i = 0; i < SkillIdList.Num(); i++)
		{
			Skill->PreExecuteSkill(SkillIdList[i]);
		}
	}
}

bool USkillComponent::CanExecuteSkill(ESkillType SkillType)
{
	return 
}
