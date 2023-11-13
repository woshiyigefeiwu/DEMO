// Copyright Epic Games, Inc. All Rights Reserved.

#include "Demo1GameMode.h"
#include "Demo1PlayerController.h"
#include "Demo1Character.h"
#include "UObject/ConstructorHelpers.h"

ADemo1GameMode::ADemo1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADemo1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}