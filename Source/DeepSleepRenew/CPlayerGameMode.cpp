// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPlayerGameMode.h"
#include "DeepSleepRenewCharacter.h"
#include "99_Other/CPlayerWidget.h"
#include "UObject/ConstructorHelpers.h"

ACPlayerGameMode::ACPlayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACPlayerGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ACPlayerGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
