// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBaseWeapon.generated.h"



class UCBaseSkillComponent;
class UCSkillManagement;
class UCStateComponent;
class ACPlayerCharacter;
class USkeletalMesh;
class ACProjectile;
class UParticleSystemComponent;

UCLASS()
class DEEPSLEEPRENEW_API ACBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	virtual FORCEINLINE int32 GetMaxAmmo(){ check(false); return 0; }
	virtual FORCEINLINE int32 GetCurrentAmmo(){ check(false); return 0; }
	virtual FORCEINLINE bool GetbisReloading(){check(false); return 0;}
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh(){return Mesh;}

	// Sets default values for this actor's properties
	ACBaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

		
protected:
	UPROPERTY()
	AActor* OwnerActor;
	
	UPROPERTY()
	ACharacter* OwnerCharacter;
	
	UPROPERTY()
	USkeletalMeshComponent* OwnerMesh;

	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	ACProjectile* Projectile;
	
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	TSubclassOf<ACProjectile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCSkillManagement* SkillManagement;

	UFUNCTION()
	virtual void GetAmmoRemainCount(){};


public:
	UFUNCTION()
	virtual void OnFire();

private:
	void SetupOwnerCharacter();
	
};
