// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DEEPSLEEP427HUD.generated.h"

UCLASS()
class ADEEPSLEEP427HUD : public AHUD
{
	GENERATED_BODY()

public:
	ADEEPSLEEP427HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

