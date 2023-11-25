#include "MyGameModeBase.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyGameStateBase.h"
#include "Demo1/Demo1Character.h"
#include "Demo1/Demo1PlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	GameStateClass = AMyGameStateBase::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();

	//FString CharacterClassLoadPath = FString(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/TopDownCharacter.TopDownCharacter_C'"));
	//DefaultPawnClass = LoadClass<ADemo1Character>(NULL, *CharacterClassLoadPath);
	//PlayerControllerClass = ADemo1PlayerController::StaticClass();
}

void AMyGameModeBase::BeginPlay()
{

}

UGeneralDataAsset* AMyGameModeBase::GetGeneralDataAsset()
{
	return GeneralDataAsset;
}

void AMyGameModeBase::PlayGame()
{
	OnPlayGame.Broadcast();
}
