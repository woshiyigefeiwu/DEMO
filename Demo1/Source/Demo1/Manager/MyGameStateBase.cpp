// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralDataAsset.h"

#include "MyGameStateBase.h"
#include "MyGameModeBase.h"

void AMyGameStateBase::BeginPlay()
{
	// 初始化一下GameState
	Init();
}

void AMyGameStateBase::Init()
{
	const AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetDefaultGameMode());
	if (GM && GM->GeneralDataAsset)
	{
		M_CampInfoList = GM->GeneralDataAsset->CampInfoList;
		M_SoldierInfoList = GM->GeneralDataAsset->SoldierInfoList;
	}
}

TArray<FCampInfo> AMyGameStateBase::GetCampInfoList()
{
	return M_CampInfoList;
}

TArray<FSoldierInfo> AMyGameStateBase::GetSoldierInfoList()
{
	//M_SoldierInfoList[0].SoldierClass.;
	return M_SoldierInfoList;
}
