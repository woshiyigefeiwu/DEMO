// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_ChangeAttributeValue.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

bool ASkill_ChangeAttributeValue::CanExecuteSkill(FString SkilleId)
{
	if (SkillComponent)
	{
		//FSkill_ChangeAttributeValue_Node Skill_ChangeAttributeValue_Node = ;
		FAttributeValue AttributeValue = GetSkillConfigNode(SkilleId).AttributeValue;		// 具体条件
		AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
		AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

		if (AI && GM && GM->GetSkillManager())
		{
			ASkillManager* SkillManager = GM->GetSkillManager();

			if (SkillManager->GetFloatAttributeValueByAttributeType(AttributeValue.Attribute, AI) <= AttributeValue.Value)
			{
				return true;
			}
		}
	}

	return false;
}

void ASkill_ChangeAttributeValue::ExecuteSkill(FString SkilleId)
{
	if (SkillComponent)
	{
		AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
		AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
		TMap<EAttributeType, float> AttributeEffectList = GetSkillConfigNode(SkilleId).AttributeEffectList;

		if (AI && GM && GM->GetSkillManager())
		{
			ASkillManager* SkillManager = GM->GetSkillManager();

			for (TMap<EAttributeType, float>::TConstIterator iter = AttributeEffectList.CreateConstIterator(); iter; ++iter)
			{
				SkillManager->SetFloatAttributeValueByAttributeType(iter->Key, iter->Value, AI);
			}
		}
	}	
}

FSkill_ChangeAttributeValue_Node ASkill_ChangeAttributeValue::GetSkillConfigNode(FString SkilleId)
{
	if (SkillComponent)
	{
		AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
		AMyGameModeBase* GM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (AI && GM && GM->GetSkillManager())
		{
			ASkillManager* SkillManager = GM->GetSkillManager();
			return SkillManager->GetSkill_ChangeAttributeValue_Node(SkillType, SkilleId);
		}
	}

	return FSkill_ChangeAttributeValue_Node();
}
