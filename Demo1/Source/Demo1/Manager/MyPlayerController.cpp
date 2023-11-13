// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::BeginPlay()
{
	GetWorldTimerManager().SetTimer(M_TimerHandle, this, &AMyPlayerController::HideMouse, 5.0f, false);
}

void AMyPlayerController::HideMouse()
{
	//bShowMouseCursor = false;
}


