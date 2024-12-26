// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/CBaseWeapon.h"
#include "CHealthCore.generated.h"


class UCHealthSkillComponent;
UCLASS()
class DEEPSLEEPRENEW_API ACHealthCore : public ACBaseWeapon
{
	GENERATED_BODY()

public:
	ACHealthCore();
	virtual void OnFire() override;
	// 델리게이트 인스턴스
	
	virtual void GetAmmoRemainCount() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY()
	UCHealthSkillComponent* HealthSkillComponent;

private:

	UPROPERTY()
	int32 MaxAmmo;

	UPROPERTY()
	int32 CurrentAmmo;

	UFUNCTION()
	void BroadcastAmmoInfo(int32 Current, int32 Max);
};
