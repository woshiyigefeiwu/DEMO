// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_ChangeAttributeValue.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ASkill_ChangeAttributeValue::ExecuteSkill()
{
	if (SkillComponent)
	{
		// ��ȡһ���Լ���������Ϣ
		TMap<EAttributeType, float> AdditionalAttributeList = GetAdditionalAttributeList();

		for (TMap<EAttributeType, float>::TConstIterator it = AdditionalAttributeList.CreateConstIterator(); it; ++it)
		{
			//if (it->Key == EAttributeType::AttachATK)		// ���ӹ�����
			//{
			//	SkillComponent->SetAttachAtk(SkillId, it->Value);
			//}
			//else if (it->Key == EAttributeType::AttachHP)	// ����Ѫ�����������Ϊ���ܣ�
			//{
			//	SkillComponent->SetAttachHp(SkillId, it->Value);
			//}
			//else if (it->Key == EAttributeType::HP)			// ֱ�����ӵ�ǰѪ��
			//{
			//	AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);
			//	if (AI)
			//	{
			//		float CurrentHp = AI->GetCurrentHp();
			//		AI->SetCurrentHP(CurrentHp + it->Value);
			//	}
			//}

			if (it->Key == EAttributeType::HP)			// ֱ�����ӵ�ǰѪ��
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

		// �ǵ�����һ���ͷż���ʱ��
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
