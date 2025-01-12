// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DEEPSLEEPRENEW_API UCAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
	UCAssetManager();

public:
	void StartInitialLoading() override;
};
