// Copyright Epic Games, Inc. All Rights Reserved.

#include "DEEPSLEEP427GameMode.h"
#include "DEEPSLEEP427/HUD/DEEPSLEEP427HUD.h"
#include "DEEPSLEEP427/Player/DEEPSLEEP427Character.h"
#include "UObject/ConstructorHelpers.h"

ADEEPSLEEP427GameMode::ADEEPSLEEP427GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADEEPSLEEP427HUD::StaticClass();
}
