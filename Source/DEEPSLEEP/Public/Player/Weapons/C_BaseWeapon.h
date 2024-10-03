// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_BaseWeapon.generated.h"

class AC_PlayerCharacter;
class USkeletalMesh;
class AC_Projectile;
class UC_ReloadComponent;
class UAnimMontage;

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


	
protected:
	UPROPERTY()
	AActor* OwnerActor;
	
	UPROPERTY()
	AC_PlayerCharacter* OwnerCharacter;
	
	UPROPERTY()
	USkeletalMeshComponent* OwnerMesh;

	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	AC_Projectile* Projectile;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TSubclassOf<AC_Projectile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "Reload")
	UC_ReloadComponent* Reload;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;
	
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UAnimMontage* FireAnimMontage;

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void PlayFireAnimMontage(UAnimMontage* MontageToPlay);

public:
	UFUNCTION()
	void OnFire();
	void SetupOwnerCharacter();
	
	

};
