// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/CBaseWeapon.h"
#include "01_Weapon/00_Component/CReloadComponent.h"
#include "Global.h"
#include "CCoreWeapon.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReceiveAmmoInfo, int32, CurrentAmmo, int32, MaxAmmo );


class UCHealthSkillComponent;
UCLASS()
class DEEPSLEEPRENEW_API ACCoreWeapon : public ACBaseWeapon
{
	GENERATED_BODY()
public:
	FORCEINLINE int32 GetMaxAmmo() {return MaxAmmo;} 
	FORCEINLINE int32 GetCurrentAmmo() {return CurrentAmmo;}
	FORCEINLINE bool GetbisReloading() {return HealthReloadComponent->GetbReloading();}
	FORCEINLINE void ReloadComplete(int32 ComCurrent, int32 ComMax){BroadcastAmmoInfo(ComCurrent,ComMax); CLog::Print(ComCurrent);}

	
	UPROPERTY(BlueprintAssignable, Category = "AmmoDelegate")
	FReceiveAmmoInfo AmmoInfo;
	
	ACCoreWeapon();
	virtual void OnFire() override;
	
	virtual void GetAmmoRemainCount() override;

protected:
	virtual void BeginPlay() override;
	void ReloadWeapon();

	UFUNCTION()
	void BroadcastAmmoInfo(int32 Current, int32 Max);

private:
	UPROPERTY()
	UCReloadComponent* HealthReloadComponent;

	UPROPERTY()
	int32 MaxAmmo = 30;

	UPROPERTY()
	int32 CurrentAmmo = MaxAmmo;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY()
	UCHealthSkillComponent* HealthSkillComponent;

};
