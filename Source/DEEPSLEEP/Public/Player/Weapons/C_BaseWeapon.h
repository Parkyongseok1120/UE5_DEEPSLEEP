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
	AC_BaseWeapon();

protected:
	virtual void BeginPlay() override;

public:	
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

public:
	UFUNCTION()
	void OnFire();
	
	

};
