// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapons/C_BaseWeapon.h"

#include "Projects.h"
#include "Util/Global.h"
#include "Components/StaticMeshComponent.h"
#include "Player/ActorComponent/C_ReloadComponent.h"
#include "Player/Weapons/C_Projectile.h"
#include "GameFramework/Character.h"

// Sets default values
AC_BaseWeapon::AC_BaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateActorComponent<UC_ReloadComponent>(this, &Reload, "Reload");

	MaxAmmo = Reload->GetRemainAmmoCount();
	

}

// Called when the game starts or when spawned
void AC_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

// Called every frame
void AC_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AC_BaseWeapon::OnFire()
{
	CheckNull(OwnerCharacter)

	if(MaxAmmo > 0)
	{
		if(ProjectileClass != nullptr)
		{
			const FRotator SpawnRotation = OwnerCharacter->GetControlRotation();
			const FVector SpawnLocation = OwnerCharacter->GetActorLocation();

			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			Projectile = GetWorld()->SpawnActor<AC_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParameters);
			if(Projectile)
			{
				Projectile->SetOwner(this);
			}
		}
		
	}
	else
	{
		Reload->Reloading();
	}
}

