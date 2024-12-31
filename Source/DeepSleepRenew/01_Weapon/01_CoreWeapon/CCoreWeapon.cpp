// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "01_Weapon/CProjectile.h"
#include "01_Weapon/00_Component/00_Skill/CHealthSkillComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "Global.h"

ACCoreWeapon::ACCoreWeapon()
{
	// HealthReloadComponent를 한 번만 생성
	CHelpers::CreateActorComponent<UCReloadComponent>(this, &HealthReloadComponent, "ReloadComponent");
	CHelpers::CreateActorComponent<UCHealthSkillComponent>(this, &HealthSkillComponent, "SkillComponent");
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
	HealthReloadComponent->SetMaxAmmo(MaxAmmo);
}

void ACCoreWeapon::OnFire()
{
	Super::OnFire();
	if (HealthReloadComponent && HealthReloadComponent->GetRemainAmmoCount() > 0 && !HealthReloadComponent->GetbReloading())
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
	else if (HealthReloadComponent && HealthReloadComponent->GetRemainAmmoCount() <= 0 && !HealthReloadComponent->GetbReloading())
	{
		// 탄약이 없을 경우 자동으로 재장전 호출
		ReloadWeapon();
	}
}



void ACCoreWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACCoreWeapon::ReloadWeapon()
{
	// HealthReloadComponent에서 재장전 로직 호출
	HealthReloadComponent->Reloading();
}


void ACCoreWeapon::BroadcastAmmoInfo(int32 Current, int32 Max)
{	
	if (this->AmmoInfo.IsBound())
	{
		this->AmmoInfo.Broadcast(Current, Max);
	}
}


void ACCoreWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACCoreWeapon::GetAmmoRemainCount()
{
	HealthReloadComponent->AmmoCounting();
	CurrentAmmo = HealthReloadComponent->GetRemainAmmoCount();
	BroadcastAmmoInfo(CurrentAmmo, MaxAmmo);
	UE_LOG(LogTemp, Log, TEXT("AmmoInfo.Broadcast called: %d/%d"), CurrentAmmo, MaxAmmo);
}

