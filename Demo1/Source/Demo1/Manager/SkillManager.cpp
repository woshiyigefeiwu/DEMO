// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillManager.h"
#include "Demo1/Skill/Skill_Base.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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

ASkill_Base* ASkillManager::CreateSkill(ESkillType SkillId)
{
	USkillConfig* SkillConfig = GetSkillConfig();
	if (SkillConfig)
	{
		if (SkillConfig->SkillLogicIdConfig.Contains(SkillId))
		{
			FSoftClassPath SoftClassPath = SkillConfig->SkillLogicIdConfig[SkillId];
			UClass* SkillClass = LoadSkillClass(SoftClassPath);
			ASkill_Base* Skill = GetWorld()->SpawnActor<ASkill_Base>(SkillClass);

			return Skill;
		}
	}

	return nullptr;
}

UClass* ASkillManager::LoadSkillClass(FSoftClassPath SoftClassPath)
{
	//FString Skill_Base_Path = "Blueprint'";
	//Skill_Base_Path.Append(SoftClassPath.ToString());
	//Skill_Base_Path.Append("'");
	FString Skill_Base_Path = SoftClassPath.ToString();
	UClass* Skill_Base_Class = LoadClass<AActor>(NULL, *Skill_Base_Path);
	return Skill_Base_Class;
}

USkillConfig* ASkillManager::GetSkillConfig()
{
	AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (GM && GM->GetGeneralDataAsset())
	{
		return GM->GetGeneralDataAsset()->SkillConfig;
	}
	return nullptr;
}

float ASkillManager::GetFloatAttributeValueByAttributeType(EAttributeType AttributeType, AAICharacter_Base* AI)
{
	if (AI)
	{
		if (AttributeType == EAttributeType::HP)
		{
			return AI->GetAllCurrentHp();
		}
		else if (AttributeType == EAttributeType::ATK)
		{
			return AI->GetAllAtk();
		}
	}

	return 0.0f;
}

void ASkillManager::SetFloatAttributeValueByAttributeType(EAttributeType AttributeType, float Value, AAICharacter_Base* AI)
{
	if (AI)
	{
		if (AttributeType == EAttributeType::AttachHP)
		{
			AI->SetAttachCurrentHP(Value);
		}
		else if (AttributeType == EAttributeType::AttachATK)
		{
			AI->SetAttachAtk(Value);
		}
	}
}

FSkill_ChangeAttributeValue_Node ASkillManager::GetSkill_ChangeAttributeValue_Node(ESkillType SkillType, FString SkilleId)
{
	USkillConfig* SkillConfig = GetSkillConfig();
	if (SkillConfig && SkillType == ESkillType::ChangeAttributeValue)
	{
		if (SkillConfig->Skill_ChangeAttributeValue_List.Contains(SkilleId))
		{
			return SkillConfig->Skill_ChangeAttributeValue_List[SkilleId];
		}
	}

	return FSkill_ChangeAttributeValue_Node();
}
