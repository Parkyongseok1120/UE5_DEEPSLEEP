// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseWeapon.generated.h"

class ACharacter;
class USkeletalMesh;
class AC_Projectile;
class UC_ReloadComponent;

UCLASS()
class DEEPSLEEP_API AC_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_BaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	AC_Projectile* Projectile;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TSubclassOf<AC_Projectile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reload")
	UC_ReloadComponent* Reload;
	
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY()
	int32 RemainAmmo;

	UPROPERTY()
	int32 UsingAmmo;

	bool bisReloading;

	void AmmoCount();
	
public:
	UFUNCTION()
	void OnFire();
	UFUNCTION()
	void ChecktoWepaonSpawn();
	
	

};
