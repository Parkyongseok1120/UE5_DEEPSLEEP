// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapons/C_Projectile.h"
#include "Util/Global.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/ActorComponent/C_ReloadComponent.h"
#include "Traster/C_TrasterBase.h"
#include "GameFramework/Character.h"
#include "Player/Weapons/C_BaseWeapon.h"


AC_Projectile::AC_Projectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UC_ReloadComponent>(this, &ReloadComponent, "Reload");
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileMovement, "Projectile");
	CHelpers::CreateComponent<USphereComponent>(this, &CollisionComp, "SphereComp");
	RootComponent = CollisionComp;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", CollisionComp);
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "/Script/Engine.StaticMesh'/Game/Mesh/SciFiWeapDark/Weapons/Darkness_RocketLauncher_Ammo.Darkness_RocketLauncher_Ammo'");
	Mesh->SetStaticMesh(mesh);
	//Mesh->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));
	
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AC_Projectile::OnHit);

	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 10000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	BaseDamage = 10;

	//탄이 3초동안 살아있음.
	InitialLifeSpan = 3.0f;
}

void AC_Projectile::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

void AC_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = Cast<ACharacter>(OwnerCharacter);
	if(MyOwner)
	{
		MakeNoise(1.0f, MyOwner->GetInstigator());
		AActor* HitActor = Hit.GetActor();
		float ActualDamage = BaseDamage;

		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();
		float HalfRad = FMath::DegreesToRadians(BulletSpread);
		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad);

		TrasterBase = Cast<AC_TrasterBase>(OtherActor);
		if(HitActor && HitActor->IsA(AC_TrasterBase::StaticClass())) //Hit된 Actor가 AC_TrasterBase거나, 그 자손일 경우
		{
			float Damage = UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(),MyOwner, DamageType);
			CLog::Print(HitActor->GetName());
		}
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

void AC_Projectile::PlayImpactEffects(FVector ImpactPoint)
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

