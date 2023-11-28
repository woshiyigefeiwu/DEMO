// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_Base.h"
#include "SkillComponent.h"

// Sets default values
ASkill_Base::ASkill_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkill_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkill_Base::Init(USkillComponent* NewSkillComponent, ESkillType NewSkillType)
{
	SkillComponent = NewSkillComponent;
	SkillType = NewSkillType;
}

void ASkill_Base::PreExecuteSkill(FString SkilleId)
{
	if (CanExecuteSkill(SkilleId))
	{
		ReduceConsume(SkilleId);
		ExecuteSkill(SkilleId);
	}
}

