// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_ChangeAttributeValue.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ASkill_ChangeAttributeValue::ExecuteSkill()
{
	if (SkillComponent)
	{
		// 获取一下自己的配置信息
		TMap<EAttributeType, float> AdditionalAttributeList = GetAdditionalAttributeList();

		for (TMap<EAttributeType, float>::TConstIterator it = AdditionalAttributeList.CreateConstIterator(); it; ++it)
		{
			//if (it->Key == EAttributeType::AttachATK)		// 附加攻击力
			//{
			//	SkillComponent->SetAttachAtk(SkillId, it->Value);
			//}
			//else if (it->Key == EAttributeType::AttachHP)	// 附加血量（可以理解为护盾）
			//{
			//	SkillComponent->SetAttachHp(SkillId, it->Value);
			//}
			//else if (it->Key == EAttributeType::HP)			// 直接增加当前血量
			//{
			//	AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
			//	if (AI)
			//	{
			//		float CurrentHp = AI->GetCurrentHp();
			//		AI->SetCurrentHP(CurrentHp + it->Value);
			//	}
			//}

			if (it->Key == EAttributeType::HP)			// 直接增加当前血量
			{
				AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
				if (AI)
				{
					float CurrentHp = AI->GetCurrentHp();
					AI->SetCurrentHP(CurrentHp + it->Value);
				}
			}
			else
			{
				SkillComponent->SetSkillAttributeValueByEAttributeType(SkillId, it->Key, it->Value);
			}
		}

		// 记得设置一下释放技能时间
		double CurrentTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
		SkillComponent->SetLastReleaseSkillTime(SkillId, CurrentTime);
	}
}

TMap<EAttributeType, float> ASkill_ChangeAttributeValue::GetAdditionalAttributeList()
{
	if (SkillComponent)
	{
		ASkillManager* SkillManager = SkillComponent->GetSkillManager();
		if (SkillManager)
		{
			FSkill_Config_Node SkillConfigNode = SkillManager->GetSkillConfigNode(SkillId);
			TMap<EAttributeType, float> AdditionalAttributeList = SkillConfigNode.TriggerEffect.AdditionalAttributeList;
			return AdditionalAttributeList;
		}
	}
	return TMap<EAttributeType, float>();
}
