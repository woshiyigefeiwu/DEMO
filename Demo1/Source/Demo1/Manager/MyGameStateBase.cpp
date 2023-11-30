// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameStateBase.h"
#include "GeneralDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "MyGameModeBase.h"
#include "Engine/World.h"

void AMyGameStateBase::BeginPlay()
{
	// 初始化一下GameState
	Init();

	// 创建 UIM
	CreateUIManager();
	if (M_UIManager)
	{
		M_UIManager->Init();
	}
}

void AMyGameStateBase::Init()
{
	const AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetDefaultGameMode());
	if (GM && GM->GeneralDataAsset)
	{
		M_CampInfoList = GM->GeneralDataAsset->CampInfoList;
		M_SoldierInfoList = GM->GeneralDataAsset->SoldierInfoList;
	}

	// 这里得初始化一下 AIList
	FCamp_Solider_AIList Camp_Solider_AIList;
	Camp_Solider_AIList.Num = 0;
	Camp_Solider_AIList.Camp_Solider_AIList.Empty();

	FCamp_AIList Camp_AIList;
	Camp_AIList.Num = 0;
	for (int i = 0; i < M_SoldierInfoList.Num(); i++)
	{
		// ----------------
		//FString AIPath = "Blueprint'";
		//AIPath.Append(M_SoldierInfoList[i].ToString());
		//AIPath.Append("'");
		//UClass* AIClass = LoadClass<AActor>(NULL, *AIPath);

		//// 通过反射，获取类的属性（...）
		//for (TFieldIterator<UProperty> it(AIClass); it; ++it)
		//{
		//	if (it->GetName() == "SoldierType")
		//	{
		//		UEnumProperty* PropertyValue = Cast<UEnumProperty>(*it);
		//		ESoldierType* Param = it->ContainerPtrToValuePtr<ESoldierType>(AIClass->GetDefaultObject());
		//		if (Param)
		//		{
		//			if ((*Param) == ESoldierType::CLOSECOMBAT)
		//			{
		//				CurrentSoldierType = ESoldierType::CLOSECOMBAT;
		//				//UE_LOG(LogTemp, Error, TEXT("this is CLOSECOMBAT"));
		//			}
		//			else if ((*Param) == ESoldierType::LONGRANGE)
		//			{
		//				CurrentSoldierType = ESoldierType::LONGRANGE;
		//				//UE_LOG(LogTemp, Error, TEXT("this is LONGRANGE"));
		//			}
		//		}
		//	}
		//}

		// ----------------

		FString AIPath = "Blueprint'";
		AIPath.Append(M_SoldierInfoList[i].ToString());
		AIPath.Append("'");
		UClass* AIClass = LoadClass<AAICharacter_Base>(NULL, *AIPath);
		
		ESoldierType CurrentSoldierType = ESoldierType::NONE;

		if (AIClass)
		{
			AAICharacter_Base* AI_Base = Cast<AAICharacter_Base>(AIClass->GetDefaultObject());
			if (AI_Base)
			{
				CurrentSoldierType = AI_Base->GetSoldierType();
			}
		}

		if (CurrentSoldierType != ESoldierType::NONE && !Camp_AIList.Camp_AIList.Contains(CurrentSoldierType))
		{
			Camp_AIList.Camp_AIList.Add(CurrentSoldierType, Camp_Solider_AIList);
		}
	}
	
	for (int i = 0; i < M_CampInfoList.Num(); i++)
	{
		M_AIList.Add(M_CampInfoList[i].Type, Camp_AIList);
	}
}

TArray<FCampInfo> AMyGameStateBase::GetCampInfoList()
{
	return M_CampInfoList;
}

TArray<FSoftClassPath> AMyGameStateBase::GetSoldierInfoList()
{
	//M_SoldierInfoList[0].SoldierClass.;
	return M_SoldierInfoList;
}

void AMyGameStateBase::SetCurrentCamp(ECampType CurrentCamp)
{
	M_CurrentCamp = CurrentCamp;
}

ECampType AMyGameStateBase::GetCurrentCamp()
{
	return M_CurrentCamp;
}

// 添加 AI
void AMyGameStateBase::AddAI(AAICharacter_Base* AI)
{
	ECampType CampType = AI->GetCampType();
	ESoldierType SoldierType = AI->GetSoldierType();

	if (M_AIList.Contains(CampType))
	{
		FCamp_AIList* Camp_AIList_Ptr = &M_AIList[CampType];
		if (Camp_AIList_Ptr->Camp_AIList.Contains(SoldierType))
		{
			FCamp_Solider_AIList* Camp_Solider_AIList_Ptr = &Camp_AIList_Ptr->Camp_AIList[SoldierType];
			
			Camp_Solider_AIList_Ptr->Camp_Solider_AIList.Add(AI);
			Camp_Solider_AIList_Ptr->Num++;
			Camp_AIList_Ptr->Num++;

			// --------------- test out -------------------------
			//UEnum* const CampType_Prt = StaticEnum<ECampType>();
			//UEnum* const SoldierType_Prt = StaticEnum<ESoldierType>();
			//auto camp_type = CampType_Prt->GetDisplayNameTextByValue(static_cast<uint8>(CampType));
			//auto soldier_type = SoldierType_Prt->GetDisplayNameTextByValue(static_cast<uint8>(SoldierType));
			//UE_LOG(LogTemp, Error, TEXT("Camp is : %s -------- Solier is : %s ---------- Camp num is : %d --------"), *camp_type.ToString(), *soldier_type.ToString(), Camp_AIList_Ptr->Num);
			//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT("Camp is : %s -------- Solier is : %s ---------- Camp num is : %d --------"), *camp_type.ToString(), *soldier_type.ToString(), Camp_AIList_Ptr->Num));
		}
	}

	OnAINumChange.Broadcast();
}

// 删除 AI
void AMyGameStateBase::DeleteAI(AAICharacter_Base* AI)
{
	ECampType CampType = AI->GetCampType();
	ESoldierType SoldierType = AI->GetSoldierType();

	if (M_AIList.Contains(CampType))
	{
		FCamp_AIList* Camp_AIList_Ptr = &M_AIList[CampType];
		if (Camp_AIList_Ptr->Camp_AIList.Contains(SoldierType))
		{
			FCamp_Solider_AIList* Camp_Solider_AIList_Ptr = &Camp_AIList_Ptr->Camp_AIList[SoldierType];

			Camp_Solider_AIList_Ptr->Camp_Solider_AIList.Remove(AI);
			Camp_Solider_AIList_Ptr->Num--;
			Camp_AIList_Ptr->Num--;

			//UEnum* const CampType_Prt = StaticEnum<ECampType>();
			//UEnum* const SoldierType_Prt = StaticEnum<ESoldierType>();
			//auto camp_type = CampType_Prt->GetDisplayNameTextByValue(static_cast<uint8>(CampType));
			//auto soldier_type = SoldierType_Prt->GetDisplayNameTextByValue(static_cast<uint8>(SoldierType));
			//UE_LOG(LogTemp, Error, TEXT("Camp is : %s -------- Solier is : %s ---------- Camp num is : %d --------"), *camp_type.ToString(), *soldier_type.ToString(), Camp_AIList_Ptr->Num);
			//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green, FString::Printf(TEXT("Camp is : %s -------- Solier is : %s ---------- Camp num is : %d --------"), *camp_type.ToString(), *soldier_type.ToString(), Camp_AIList_Ptr->Num));
		}
	}

	// 一方阵亡
	if (M_AIList.Contains(CampType) && M_AIList[CampType].Num <= 0)
	{
		// 抛事件出去，PC
		GameOverDelegate.Broadcast();
	}

	OnAINumChange.Broadcast();
}

AUIManager* AMyGameStateBase::GetUIManager()
{
	return M_UIManager;
}

void AMyGameStateBase::CreateUIManager()
{
	M_UIManager = GWorld->SpawnActor<AUIManager>();
}

int AMyGameStateBase::GetNumByCampType(ECampType CampType)
{
	if (M_AIList.Contains(CampType))
	{
		return M_AIList[CampType].Num;
	}

	return 0;
}

int AMyGameStateBase::GetNumByCampSoliderType(ECampType CampType, ESoldierType SoldierType)
{
	if (M_AIList.Contains(CampType))
	{
		FCamp_AIList* Camp_AIList_Ptr = &M_AIList[CampType];
		if (Camp_AIList_Ptr->Camp_AIList.Contains(SoldierType))
		{
			return Camp_AIList_Ptr->Camp_AIList[SoldierType].Num;
		}
	}

	return 0;
}

UClass* AMyGameStateBase::LoadClass_AIBase(FSoftClassPath SoftClassPath)
{
	FString AIPath = "Blueprint'";
	AIPath.Append(SoftClassPath.ToString());
	AIPath.Append("'");
	UClass* AIClass = LoadClass<AActor>(NULL, *AIPath);
	return AIClass;
}

AAICharacter_Base* AMyGameStateBase::GetDefaultObject_AIBase(FSoftClassPath SoftClassPath)
{
	UClass* AIClass = LoadClass_AIBase(SoftClassPath);
	if (AIClass)
	{
		AAICharacter_Base* DefaultObject_AIBase = Cast<AAICharacter_Base>(AIClass->GetDefaultObject());
		return DefaultObject_AIBase;
	}
	return nullptr;
}

ESoldierType AMyGameStateBase::GetSoliderType(FSoftClassPath AIClassPath)
{
	for (int i = 0; i < M_SoldierInfoList.Num(); i++)
	{
		if (AIClassPath == M_SoldierInfoList[i])
		{
			AAICharacter_Base* DefaultObject_AIBase = GetDefaultObject_AIBase(AIClassPath);
			if (DefaultObject_AIBase)
			{
				return DefaultObject_AIBase->GetSoldierType();
			}	
		}
	}	

	return ESoldierType();
}

FString AMyGameStateBase::GetDisplayStrBySoliderType(ESoldierType SoldierType)
{
	for (int i = 0; i < M_SoldierInfoList.Num(); i++)
	{
		AAICharacter_Base* DefaultObject_AIBase = GetDefaultObject_AIBase(M_SoldierInfoList[i]);
		if (DefaultObject_AIBase->GetSoldierType() == SoldierType)
		{
			return DefaultObject_AIBase->GetDisplayStr();
		}
	}

	return FString();
}

TArray<AAICharacter_Base*> AMyGameStateBase::GetFriends(ECampType CampType)
{
	TArray<AAICharacter_Base*> AIArray;
	if (M_AIList.Contains(CampType))
	{
		for (TMap<ESoldierType, FCamp_Solider_AIList>::TConstIterator it = M_AIList[CampType].Camp_AIList.CreateConstIterator(); it; ++it)
		{
			for (int i = 0; i < it->Value.Camp_Solider_AIList.Num(); i++)
			{
				AAICharacter_Base* AI = it->Value.Camp_Solider_AIList[i];
				if (AI && !AI->IsDead())
				{
					AIArray.Add(AI);
				}
			}
		}
	}
	return AIArray;
}





