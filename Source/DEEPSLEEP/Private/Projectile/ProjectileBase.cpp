// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile//ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Player/Deepsleep_LegacyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	BaseDamage=20.f;
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 20000.f;
	ProjectileMovement->MaxSpeed = 20000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.f;

}
void AProjectileBase::PlayImpactEffects(FVector ImpactPoint)
{
	UParticleSystem* SelectedEffect = nullptr;
	if(DefaultImpactEffect)
	{
		SelectedEffect = DefaultImpactEffect;
	}
	if (SelectedEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, ImpactPoint);
	}
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if(MyOwner)
	{
		MakeNoise(1.0f, MyOwner->GetInstigator());
		AActor* HitActor = Hit.GetActor();
		float ActualDamage = BaseDamage;
		ActualDamage *= 1.0f;

		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		float HalfRad = FMath::DegreesToRadians(BulletSpread);
		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

		UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(),MyOwner, DamageType);

		FVector TracerEnd = EyeLocation +(ShotDirection * 90000);
		FVector TracerEndPoint = TracerEnd;
		PlayImpactEffects(Hit.ImpactPoint);
		TracerEndPoint = Hit.ImpactPoint;
	}
	Destroy();
	
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

