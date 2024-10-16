// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Weapons/C_BaseWeapon.h"
#include "Util/Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"

#include "Player/Weapons/C_ReloadComponent.h"
#include "Player/Weapons/C_Projectile.h"
#include "GameFramework/Character.h"
#include "Player/C_PlayerCharacter.h"

// Sets default values
AC_BaseWeapon::AC_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	

	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateActorComponent<UC_ReloadComponent>(this, &Reload, "Reload");
	CHelpers::GetAsset<UAnimMontage>(&FireAnimMontage, "/Script/Engine.AnimMontage'/Game/Characters/Dummy/Anim/Pistol/Shooting_Montage.Shooting_Montage'");
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
	
	
	ProjectileClass = AC_Projectile::StaticClass();
	if(Projectile)
	{
		Projectile->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("Muzzle"));
	}
}

void AC_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_BaseWeapon::SetupOwnerCharacter()
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

void AC_BaseWeapon::OnFire()
{
	OwnerCharacter = Cast<AC_PlayerCharacter>(GetOwner());
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
				PlayFireAnimMontage(FireAnimMontage);
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
void AC_BaseWeapon::PlayFireAnimMontage(UAnimMontage* MontageToPlay)
{
	if(OwnerCharacter)
	{
		if (MontageToPlay)
		{
			OwnerCharacter->PlayAnimMontage(MontageToPlay, 1);
			CLog::Print("Montage_Play");
		}
	}
	


}


