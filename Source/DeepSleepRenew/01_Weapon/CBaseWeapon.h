// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBaseWeapon.generated.h"

class ACPlayerCharacter;
class USkeletalMesh;
class ACProjectile;
class UCReloadComponent;
class UParticleSystemComponent;

UCLASS()
class DEEPSLEEPRENEW_API ACBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
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

	UPROPERTY(VisibleDefaultsOnly, Category = "Reload")
	UCReloadComponent* Reload;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* MuzzleLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UParticleSystem* CoreParticle;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configurations")
	FTransform PlacementTransform; //무기의 위치를 표시하는 것이다.
public:
	UFUNCTION()
	void OnFire();
	void SetupOwnerCharacter();
	
};
