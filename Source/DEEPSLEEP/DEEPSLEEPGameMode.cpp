// Copyright Epic Games, Inc. All Rights Reserved.

#include "DEEPSLEEPGameMode.h"
#include "Player/DEEPSLEEPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADEEPSLEEPGameMode::ADEEPSLEEPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
