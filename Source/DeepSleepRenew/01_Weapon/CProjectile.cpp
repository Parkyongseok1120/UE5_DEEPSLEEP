// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/CProjectile.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "00_Component/CReloadComponent.h"
#include "00_Character/01_Monster/CBaseMonster.h"
#include "GameFramework/Character.h"

// Sets default values
ACProjectile::ACProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateActorComponent<UCReloadComponent>(this, &ReloadComponent, "Reload");
	CHelpers::CreateActorComponent<UProjectileMovementComponent>(this, &ProjectileMovement, "Projectile");
	CHelpers::CreateComponent<USphereComponent>(this, &CollisionComp, "SphereComp");
	RootComponent = CollisionComp;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", CollisionComp);
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "/Script/Engine.StaticMesh'/Game/VFX_Toolkit_V1/StaticMeshes/Various/SM_Meteora.SM_Meteora'");
	Mesh->SetStaticMesh(mesh);
	//Mesh->SetRelativeScale3D(FVector(0.2f,0.2f,0.2f));


	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACProjectile::OnHit);

	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 10000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	BaseDamage = 10;

	//탄이 3초동안 살아있음.
	InitialLifeSpan = 3.0f;

}

// Called when the game starts or when spawned
void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());

}

// Called every frame
void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
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

		TrasterBase = Cast<ACBaseMonster>(OtherActor);
		if(HitActor && HitActor->IsA(ACBaseMonster::StaticClass())) //Hit된 Actor가 ACBaseTraster이거나, 그 자손일 경우
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

void ACProjectile::PlayImpactEffects(FVector ImpactPoint)
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
