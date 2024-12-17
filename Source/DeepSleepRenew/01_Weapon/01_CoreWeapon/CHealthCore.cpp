// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/01_CoreWeapon/CHealthCore.h"
#include "01_Weapon/00_Component/CReloadComponent.h"
#include "01_Weapon/00_Component//CSkillManagement.h"
#include "01_Weapon/00_Component//CBaseSkillComponent.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "01_Weapon/CProjectile.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "Global.h"
#include "01_Weapon/00_Component/00_Skill/CHealthSkillComponent.h"

ACHealthCore::ACHealthCore()
{
	CHelpers::CreateActorComponent<UCHealthSkillComponent>(this, &HealthSkillComponent, "SkillComponent");
	CHelpers::CreateComponent<USkeletalMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &ParticleComponent, "Particle", Mesh);
	CHelpers::GetAsset<UParticleSystem>(&CoreParticle, "/Script/Engine.ParticleSystem'/Game/VFX_Toolkit_V1/ParticleSystems/356Days/Par_SparCore_01.Par_SparCore_01'");
	ParticleComponent->SetTemplate(CoreParticle);
	ParticleComponent->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	
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

void ACHealthCore::OnFire()
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
				Reload->AmmoCounting();
			
			}
		}
	}
	else if(Reload->GetRemainAmmoCount() <= 0)
	{
		Reload->Reloading();
	}
}

void ACHealthCore::BeginPlay()
{
	Super::BeginPlay();
}

void ACHealthCore::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
