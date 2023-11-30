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

UClass* ASkillManager::LoadSkillExecutorClass(FSoftClassPath SoftClassPath)
{
	FString Skill_Base_Path = SoftClassPath.ToString();
	UClass* Skill_Base_Class = LoadClass<AActor>(NULL, *Skill_Base_Path);
	return Skill_Base_Class;
}

ASkill_Base* ASkillManager::CreateSkillExecutor(FString SkillId)
{
	FSkill_Config_Node SkillConfigNode = GetSkillConfigNode(SkillId);
	FSoftClassPath ExecutorClassPath = SkillConfigNode.TriggerEffect.SkillEffectExecutor;

	UClass* ExecutorClass = LoadSkillExecutorClass(ExecutorClassPath);
	ASkill_Base* Skill = GetWorld()->SpawnActor<ASkill_Base>(ExecutorClass);

	return Skill;
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

bool ASkillManager::IsInSkillConfigList(FString SkillId)
{
	USkillConfig* SkillConfig = GetSkillConfig();
	if (SkillConfig)
	{
		return SkillConfig->SkillConfigList.Contains(SkillId);
	}

	return false;
}

FSkill_Config_Node ASkillManager::GetSkillConfigNode(FString SkillId)
{
	USkillConfig* SkillConfig = GetSkillConfig();
	if (SkillConfig && SkillConfig->SkillConfigList.Contains(SkillId))
	{
		return SkillConfig->SkillConfigList[SkillId];
	}

	return FSkill_Config_Node();
}

FString ASkillManager::GetSkillConsumeList(FString SkillId)
{
	return FString();
}

bool ASkillManager::CheckTriggerCondition(FString SkillId, AActor* Actor)
{
	FSkill_Config_Condition_Node TriggerCondition = GetSkillConfigNode(SkillId).TriggerCondition;

	// 根据不同的触发条件类型，做具体的判断
	if (TriggerCondition.TriggerConditionType == ETriggerCondition::NONE)
	{
		return true;
	}
	else if (TriggerCondition.TriggerConditionType == ETriggerCondition::LessThan)
	{
		return CheckTriggerCondition_LessThan(TriggerCondition, Actor);
	}
	else if (TriggerCondition.TriggerConditionType == ETriggerCondition::GreaterThan)
	{
		return CheckTriggerCondition_GreaterThan(TriggerCondition, Actor);
	}

	return false;
}

bool ASkillManager::CheckTriggerCondition_LessThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor)
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(Actor);
	if (AI)
	{
		float AIAttributeValue = GetValueByAttributeType(TriggerCondition.TriggerConditionAttributeValue.Attribute, AI);
		//UE_LOG(LogTemp, Error, TEXT("CurrentHp : %f"), AIAttributeValue);
		//UE_LOG(LogTemp, Error, TEXT("ConditionHp : %f"), TriggerCondition.TriggerConditionAttributeValue.Value);
		//UE_LOG(LogTemp, Error, TEXT("------------------"));
		return AIAttributeValue < TriggerCondition.TriggerConditionAttributeValue.Value;
	}

	return false;
}

bool ASkillManager::CheckTriggerCondition_GreaterThan(FSkill_Config_Condition_Node TriggerCondition, AActor* Actor)
{
	AAICharacter_Base* AI = Cast<AAICharacter_Base>(Actor);
	if (AI)
	{
		float AIAttributeValue = GetValueByAttributeType(TriggerCondition.TriggerConditionAttributeValue.Attribute, AI);
		return AIAttributeValue > TriggerCondition.TriggerConditionAttributeValue.Value;
	}

	return false;
}

float ASkillManager::GetValueByAttributeType(EAttributeType AttributeType, AAICharacter_Base* AI)
{
	if (AI)
	{
		if (AttributeType == EAttributeType::HP)
		{
			return AI->GetCurrentHp();
		}
		else if (AttributeType == EAttributeType::ATK)
		{
			return AI->GetAtk();
		}
		else if (AttributeType == EAttributeType::TotalHp)
		{
			return AI->GetTotalCurrentHp();
		}
		else if (AttributeType == EAttributeType::TotalAtk)
		{
			return AI->GetTotalAtk();
		}
	}

	return 0.0f;
}
