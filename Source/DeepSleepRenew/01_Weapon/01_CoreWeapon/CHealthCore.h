// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/CBaseWeapon.h"
#include "CHealthCore.generated.h"


UCLASS()
class DEEPSLEEPRENEW_API ACHealthCore : public ACBaseWeapon
{
	GENERATED_BODY()

public:
	ACHealthCore();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
};
