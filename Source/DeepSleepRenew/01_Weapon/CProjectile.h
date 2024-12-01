// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

class ACharacter;
class ACBaseMonster;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class UDamageType;
class UCReloadComponent;
class UStaticMeshComponent;

UCLASS()
class DEEPSLEEPRENEW_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY()
	ACBaseMonster* TrasterBase;

	UPROPERTY(VisibleDefaultsOnly)
	UCReloadComponent* ReloadComponent;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category=Projectile)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	virtual void PlayImpactEffects(FVector ImpactPoint);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponEffect")
	UParticleSystem* DefaultImpactEffect;

	UParticleSystemComponent* ParticleComponent;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DamageType")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta = (ClampMin = 0.0f))
	float BulletSpread;

};
