// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManager.h"
#include "Demo1/Skill/Skill_Base.h"

// Sets default values
ASkillManager::ASkillManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ASkill_Base* ASkillManager::CreateSkill(FString SkillId)
{
	if (SkillIdConfig.Contains(SkillId))
	{
		FSoftClassPath SoftClassPath = SkillIdConfig[SkillId];
		UClass* SkillClass = LoadSkillClass(SoftClassPath);
		ASkill_Base* Skill = GetWorld()->SpawnActor<ASkill_Base>(SkillClass);

		return Skill;
	}

	return nullptr;
}

UClass* ASkillManager::LoadSkillClass(FSoftClassPath SoftClassPath)
{
	FString Skill_Base_Path = "Blueprint'";
	Skill_Base_Path.Append(SoftClassPath.ToString());
	Skill_Base_Path.Append("'");
	UClass* Skill_Base_Class = LoadClass<AActor>(NULL, *Skill_Base_Path);
	return Skill_Base_Class;
}