// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapons/C_BaseWeapon.h"
#include "Util/Global.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Player/ActorComponent/C_ReloadComponent.h"
#include "GameFramework/Character.h"



AC_BaseWeapon::AC_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UC_ReloadComponent>(this, &ReloadComponent, "Reload");
	CHelpers::CreateComponent<USphereComponent>(this, &CollisionComp, "SphereComp" );
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AC_BaseWeapon::OnHit);	
}

void AC_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

void AC_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AC_BaseWeapon::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

	
}

void AC_BaseWeapon::PlayImpactEffects(FVector ImpactPoint)
{
}

