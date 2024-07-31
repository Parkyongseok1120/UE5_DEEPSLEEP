// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DEEPSLEEP_Player_GameMode.h"
#include "Util/Global.h"


ADEEPSLEEP_Player_GameMode::ADEEPSLEEP_Player_GameMode()
{
	CHelpers::GetClass<APawn>(&DefaultPawnClass, "/Script/Engine.Blueprint'/Game/Blueprints/Player/BPCPlayerCharacter.BPCPlayerCharacter_C'");
}
