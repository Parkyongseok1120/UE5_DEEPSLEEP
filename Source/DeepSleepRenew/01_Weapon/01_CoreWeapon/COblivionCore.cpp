// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/01_CoreWeapon/COblivionCore.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "01_Weapon/CProjectile.h"
#include "01_Weapon/00_Component/00_Skill/CHealthSkillComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "Global.h"

ACOblivionCore::ACOblivionCore()
{
	// HealthReloadComponent를 한 번만 생성
	OblivionReloadComponent = CreateDefaultSubobject<UCReloadComponent>(TEXT("HealthReloadComponent"));
	OblivionReloadComponent->SetMaxAmmo(MaxAmmo);

	// ReloadComponents 배열에 추가 (다중 재장전 컴포넌트 관리용)
	ReloadComponents.Add(OblivionReloadComponent);
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
	if (OblivionReloadComponent && OblivionReloadComponent->GetRemainAmmoCount() > 0 && !OblivionReloadComponent->GetbReloading())
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
	else if (OblivionReloadComponent && OblivionReloadComponent->GetRemainAmmoCount() <= 0 && !OblivionReloadComponent->GetbReloading())
	{
		// 탄약이 없을 경우 자동으로 재장전 호출
		ReloadWeapon();
	}
}


void ACOblivionCore::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACOblivionCore::ReloadWeapon()
{
	// HealthReloadComponent를 바로 사용
	if (OblivionReloadComponent && !OblivionReloadComponent->GetbReloading())
	{
		// HealthReloadComponent에서 재장전 로직 호출
		OblivionReloadComponent->Reloading();
	}
}

void ACOblivionCore::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACOblivionCore::BroadcastAmmoInfo(int32 Current, int32 Max)
{
	Super::BroadcastAmmoInfo(Current, Max);
	
	if (this->AmmoInfo.IsBound())
	{
		this->AmmoInfo.Broadcast(CurrentAmmo, MaxAmmo);
	}
}


void ACOblivionCore::GetAmmoRemainCount()
{
	OblivionReloadComponent->AmmoCounting();
	CurrentAmmo = OblivionReloadComponent->GetRemainAmmoCount();
	BroadcastAmmoInfo(CurrentAmmo, MaxAmmo);
	UE_LOG(LogTemp, Log, TEXT("AmmoInfo.Broadcast called: %d/%d"), CurrentAmmo, MaxAmmo);

	// 탄약이 없을 경우 재장전 호출
	if (CurrentAmmo <= 0 && !OblivionReloadComponent->GetbReloading())
	{
		OblivionReloadComponent->Reloading();
		UE_LOG(LogTemp, Log, TEXT("AmmoInfo.Broadcast called: %d/%d"), CurrentAmmo, MaxAmmo);
	}
}

