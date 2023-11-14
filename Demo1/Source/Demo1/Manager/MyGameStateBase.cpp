// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include "MyGameModeBase.h"

void AMyGameStateBase::Init(UGeneralDataAsset* GeneralDataAsset)
{
	if (GeneralDataAsset)
	{
		M_CampInfoList = GeneralDataAsset->CampInfoList;
		M_SoldierInfoList = GeneralDataAsset->SoldierInfoList;
	}
}

void AMyGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	const AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetDefaultGameMode());
	if (GM && GM->GeneralDataAsset)
	{
		Init(GM->GeneralDataAsset);
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
