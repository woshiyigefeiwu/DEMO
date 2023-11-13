// Copyright Epic Games, Inc. All Rights Reserved.

#include "Demo_1GameMode.h"
#include "Demo_1Character.h"
#include "UObject/ConstructorHelpers.h"

ADemo_1GameMode::ADemo_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
