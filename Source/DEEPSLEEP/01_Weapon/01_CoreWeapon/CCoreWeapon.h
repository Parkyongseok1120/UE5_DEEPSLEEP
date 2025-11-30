// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/00_Component/CReloadComponent.h"
#include "Global.h"
#include "CCoreWeapon.generated.h"

class ACPlayerCharacter;
class UCSkillManagement;
class UCStateComponent;
class ACProjectile;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReceiveAmmoInfo, int32, CurrentAmmo, int32, MaxAmmo);


class UCHealthSkillComponent;
UCLASS()
class DEEPSLEEP_API ACCoreWeapon : public AActor
{
	GENERATED_BODY()
public:
	FORCEINLINE int32 GetMaxAmmo() {return MaxAmmo;} 
	FORCEINLINE int32 GetCurrentAmmo() {return CurrentAmmo;}
	FORCEINLINE UCReloadComponent* GetReloadComponent() const { return HealthReloadComponent; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return Mesh; }

	FORCEINLINE void ReloadComplete(int32 ComCurrent, int32 ComMax){BroadcastAmmoInfo(ComCurrent,ComMax); CLog::Print(ComCurrent);}

	
	UPROPERTY(BlueprintAssignable, Category = "AmmoDelegate")
	FReceiveAmmoInfo AmmoInfo;
	
	ACCoreWeapon();
	
	void OnFire(ACPlayerCharacter* OwnerC);
	void GetAmmoRemainCount();

private:
	
	ACPlayerCharacter* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	ACProjectile* Projectile;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TSubclassOf<ACProjectile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCSkillManagement* SkillManagement;

	
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
	
	bool bIsCurrentlyReloading = false;


public:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY()
	UCHealthSkillComponent* HealthSkillComponent;

};
