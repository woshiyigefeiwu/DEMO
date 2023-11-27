// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillComponent.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Skill_Base.h"

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
	Owner = GetOwner();
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(Owner);
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
	for (int i = 0; i < SkillList.Num(); i++)
	{
		UClass* SkillClass = LoadSkillClass(SkillList[i]);
		ASkill_Base* Skill = GetWorld()->SpawnActor<ASkill_Base>(SkillClass);

		if (Skill)
		{
			Skill->Init(this);
		}
	}
}

UClass* USkillComponent::LoadSkillClass(FSoftClassPath SoftClassPath)
{
	FString Skill_Base_Path = "Blueprint'";
	Skill_Base_Path.Append(SoftClassPath.ToString());
	Skill_Base_Path.Append("'");
	UClass* Skill_Base_Class = LoadClass<AActor>(NULL, *Skill_Base_Path);
	return Skill_Base_Class;
}


