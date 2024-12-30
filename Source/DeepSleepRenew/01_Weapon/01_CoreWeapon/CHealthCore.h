// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/CBaseWeapon.h"
#include "01_Weapon/00_Component/CReloadComponent.h"
#include "CHealthCore.generated.h"


class UCHealthSkillComponent;
UCLASS()
class DEEPSLEEPRENEW_API ACHealthCore : public ACBaseWeapon
{
	GENERATED_BODY()
public:
	FORCEINLINE int32 GetMaxAmmo() override {return MaxAmmo;} 
	FORCEINLINE int32 GetCurrentAmmo() override {return CurrentAmmo;}
	FORCEINLINE bool GetbisReloading()override {return HealthReloadComponent->GetbReloading();}

	
	ACHealthCore();
	virtual void OnFire() override;
	
	virtual void GetAmmoRemainCount() override;

protected:
	virtual void BeginPlay() override;
	virtual void ReloadWeapon() override;
	virtual void BroadcastAmmoInfo(int32 Current, int32 Max) override;

private:
	UPROPERTY()
	UCReloadComponent* HealthReloadComponent;


public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY()
	UCHealthSkillComponent* HealthSkillComponent;
	
};
