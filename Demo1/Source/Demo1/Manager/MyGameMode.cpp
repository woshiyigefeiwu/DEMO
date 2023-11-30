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
}

void AMyGameMode::BeginPlay()
{
}
