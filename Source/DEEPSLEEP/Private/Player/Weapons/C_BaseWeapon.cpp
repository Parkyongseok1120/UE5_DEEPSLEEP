// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapons/C_BaseWeapon.h"
#include "Util/Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

#include "Player/ActorComponent/C_ReloadComponent.h"
#include "Player/Weapons/C_Projectile.h"
#include "GameFramework/Character.h"

// Sets default values
AC_BaseWeapon::AC_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateActorComponent<UC_ReloadComponent>(this, &Reload, "Reload");

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/Mesh/SciFiWeapDark/Weapons/Darkness_Pistol.Darkness_Pistol'");
	Mesh->SetSkeletalMesh(mesh);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(Mesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

void AC_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	ProjectileClass = AC_Projectile::StaticClass();
	
	Projectile->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Muzzle"));
}

void AC_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_BaseWeapon::OnFire()
{
	if(Reload->GetRemainAmmoCount() > 0 && Reload->GetbReloading() != true)
	{
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				CLog::Print("Load");
				const FRotator SpawnRotation =  OwnerCharacter->GetControlRotation();
				const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
	
				FActorSpawnParameters ActorSpawnParameters;
				ActorSpawnParameters.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				Projectile = GetWorld()->SpawnActor<AC_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParameters);
				if(Projectile)
				{
					Projectile->SetOwner(this);
				}
				Reload->AmmoCounting();
			}
		}
	}
	else if(Reload->GetRemainAmmoCount() <= 0)
	{
		Reload->Reloading();
	}
}

