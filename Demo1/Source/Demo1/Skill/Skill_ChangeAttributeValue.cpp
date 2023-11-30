// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill_ChangeAttributeValue.h"
#include "Demo1/AICharacter/AICharacter_Base.h"
#include "Demo1/Manager/MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Demo1/Manager/MyGameStateBase.h"

void ASkill_ChangeAttributeValue::ExecuteSkill(USkillComponent* SkillComponent, TMap<FString, float> FloatMap, TMap<FString, FSoftClassPath> SoftClassPathMap)
{
	if (SkillComponent)
	{
		for (TMap<FString, float>::TConstIterator it = FloatMap.CreateConstIterator(); it; ++it)
		{
			FString s = it->Key;
			if (s == "Attribute_AttachATK")
			{
				float value = 0.0f;
				if (FloatMap.Contains("Attribute_AttachATK_Value"))
				{
					value = FloatMap["Attribute_AttachATK_Value"];
				}

				EAttributeType AttributeType = SkillComponent->GetAttributeType(it->Value);
				SkillComponent->SetSkillAttributeValueByEAttributeType(SkillId, AttributeType, value);
			}
			else if(s == "Attribute_HP")
			{
				float value = 0.0f;
				if (FloatMap.Contains("Attribute_HP_Value"))
				{
					value = FloatMap["Attribute_HP_Value"];
				}

				AAICharacter_Base* AI = Cast<AAICharacter_Base>(SkillComponent->MyOwner);

				// 作用对象是自友军
				if (FloatMap.Contains("Action_Object_Friend"))
				{
					if (AI)
					{
						AMyGameStateBase* GS = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
						TArray<AAICharacter_Base*> Friends = GS->GetFriends(AI->GetCampType());
						for (int i = 0; i < Friends.Num(); i++)
						{
							if (Friends[i])
							{
								float CurrentHp = Friends[i]->GetCurrentHp();
								CurrentHp = Friends[i]->SetCurrentHP(CurrentHp + value);
								if (CurrentHp > Friends[i]->GetMaxHp())
								{
									Friends[i]->SetMaxHp(CurrentHp);
								}
							}
						}
					}
				}
				// 作用对象是自己
				else
				{
					if (AI)
					{
						float CurrentHp = AI->GetCurrentHp();
						CurrentHp = AI->SetCurrentHP(CurrentHp + value);
						if (CurrentHp > AI->GetMaxHp())
						{
							AI->SetMaxHp(CurrentHp);
						}
					}
				}
			}
		}

		// 记得设置一下释放技能时间
		double CurrentTime = FDateTime::Now().GetTimeOfDay().GetTotalMilliseconds();
		SkillComponent->SetLastReleaseSkillTime(SkillId, CurrentTime);
	}
}
