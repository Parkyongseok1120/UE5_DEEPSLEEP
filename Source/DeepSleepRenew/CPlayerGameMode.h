// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPlayerGameMode.generated.h"

UCLASS(minimalapi)
class ACPlayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPlayerGameMode();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	
};



