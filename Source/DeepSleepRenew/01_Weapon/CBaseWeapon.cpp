// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/CBaseWeapon.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "00_Component/CReloadComponent.h"
#include "CProjectile.h"
#include "00_Character/00_Player/CPlayerCharacter.h"


// Sets default values
ACBaseWeapon::ACBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateActorComponent<UCReloadComponent>(this, &Reload, "Reload");
	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "/Script/Engine.SkeletalMesh'/Game/VFX_Toolkit_V1/SkeletalMeshes/SKM_SparCore_core_01.SKM_SparCore_core_01'");
	
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(Mesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void ACBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	ProjectileClass = ACProjectile::StaticClass();
	if(Projectile)
	{
		Projectile->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Muzzle"));
	}
	Mesh->SetVisibility(false);
}

// Called every frame
void ACBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBaseWeapon::SetupOwnerCharacter()
{
	if (OwnerCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("OwnerCharacter set successfully to %s"), *OwnerCharacter->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to cast Owner to AC_PlayerCharacter. Owner class: %s"), *OwnerActor->GetClass()->GetName());
	
	}
}

void ACBaseWeapon::OnFire()
{
	OwnerCharacter = Cast<ACPlayerCharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		CLog::Log("OnFire() called but OwnerCharacter is null. Attempting to set it up.");
		if (!OwnerCharacter)
		{
			CLog::Log("Failed to set up OwnerCharacter. Cannot fire.");
			return;
		}
	}
	if(Reload->GetRemainAmmoCount() > 0 && Reload->GetbReloading() != true)
	{
		if (OwnerCharacter == nullptr)
		{
			CLog::Log("AC_BaseWeapon::OnFire: OwnerCharacter is NULL");
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
				Reload->AmmoCounting();
			
			}
		}
	}
	else if(Reload->GetRemainAmmoCount() <= 0)
	{
		Reload->Reloading();
	}
}