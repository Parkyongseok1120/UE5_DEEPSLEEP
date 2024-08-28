// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Projectile.generated.h"

class ACharacter;
class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystem;
class UDamageType;
class UC_ReloadComponent;

UCLASS()
class DEEPSLEEP_API AC_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Projectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY(VisibleDefaultsOnly)
	UC_ReloadComponent* ReloadComponent;

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;
	
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DamageType")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Weapon", meta = (ClampMin = 0.0f))
	float BulletSpread;

};
