// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/CBaseWeapon.h"
#include "01_Weapon/00_Component/CReloadComponent.h"

#include "COblivionCore.generated.h"

UCLASS()
class DEEPSLEEPRENEW_API ACOblivionCore : public ACBaseWeapon
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetMaxAmmo() override {return MaxAmmo;} 
	FORCEINLINE int32 GetCurrentAmmo() override {return CurrentAmmo;}
	FORCEINLINE bool GetbisReloading()override {return Reload->GetbReloading();}

	ACOblivionCore();

	virtual void OnFire() override;
	
	virtual void GetAmmoRemainCount() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
