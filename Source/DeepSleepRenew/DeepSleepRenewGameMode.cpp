// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeepSleepRenewGameMode.h"
#include "DeepSleepRenewCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeepSleepRenewGameMode::ADeepSleepRenewGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
