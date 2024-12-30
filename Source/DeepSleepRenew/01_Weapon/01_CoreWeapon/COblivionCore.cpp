// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/01_CoreWeapon/COblivionCore.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "01_Weapon/CProjectile.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "Global.h"

// Sets default values
ACOblivionCore::ACOblivionCore()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/Mesh/SciFiWeapDark/Weapons/Darkness_Knife.Darkness_Knife'");
	Mesh->SetSkeletalMesh(mesh);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(Mesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	Mesh->SetVisibility(false);
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void ACOblivionCore::OnFire()
{
	Super::OnFire();
	if(Reload->GetRemainAmmoCount() > 0 && Reload->GetbReloading() != true)
	{
		if (OwnerCharacter == nullptr)
		{
			CLog::Log("ACHealthCore::OnFire: OwnerCharacter is NULL");
		}
		else
		{
			if (ProjectileClass != nullptr)
			{
				const FRotator SpawnRotation =  OwnerCharacter->GetControlRotation();
				const FVector SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
	
				UWorld* const World = GetWorld();
				if (World != nullptr)
				{
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
					ActorSpawnParams.Owner = OwnerCharacter;

					World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				}
				GetAmmoRemainCount();
			}
		}
	}
}

void ACOblivionCore::GetAmmoRemainCount()
{
	Reload->AmmoCounting();
	CurrentAmmo = Reload->GetRemainAmmoCount();
	BroadcastAmmoInfo(CurrentAmmo, MaxAmmo);
	UE_LOG(LogTemp, Log, TEXT("AmmoInfo.Broadcast called: %d/%d"), CurrentAmmo, MaxAmmo);
	if(CurrentAmmo <= 0)
	{
		Reload->Reloading();
		UE_LOG(LogTemp, Log, TEXT("AmmoInfo.Broadcast called: %d/%d"), CurrentAmmo, MaxAmmo);
	}
}

// Called when the game starts or when spawned
void ACOblivionCore::BeginPlay()
{
	Super::BeginPlay();
	Reload->SetMaxAmmo(MaxAmmo);

}

// Called every frame
void ACOblivionCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

