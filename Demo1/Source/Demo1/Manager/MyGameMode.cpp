// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyGameStateBase.h"
#include "Demo1/Demo1Character.h"
#include "Demo1/Demo1PlayerController.h"

AMyGameMode::AMyGameMode()
{
	GameStateClass = AMyGameStateBase::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

	//FString CharacterClassLoadPath = FString(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/TopDownCharacter.TopDownCharacter_C'"));
	//DefaultPawnClass = LoadClass<ADemo1Character>(NULL, *CharacterClassLoadPath);
	//PlayerControllerClass = ADemo1PlayerController::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	//CreateGeneralConfig();
}

//void AMyGameMode::CreateGeneralConfig()
//{
	//FString GeneralConfigPath = FString(TEXT("Blueprint'/Game/Demo/BluePrints/Manager/BP_GeneralConfig.BP_GeneralConfig_C'"));	// ◊¢“‚ «¿∂Õº¿‡
	//UClass* GeneralConfigClass = LoadClass<AGeneralConfig>(NULL, *GeneralConfigPath);
	//M_GeneralConfig = GetWorld()->SpawnActor<AGeneralConfig>(GeneralConfigClass);

	//AMyGameStateBase* GS = GetGameState<AMyGameStateBase>();
	//if (GS)
	//{
	//	GS->Init(M_GeneralConfig);
	//}
//}

//AGeneralConfig* AMyGameMode::GetGeneralConfig()
//{
//	return M_GeneralConfig;
//}
