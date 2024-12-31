// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/CBaseWeapon.h"
#include "00_Component/CReloadComponent.h"
#include "00_Component/CSkillManagement.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "CProjectile.h"

#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

#include "Global.h"


// Sets default values
ACBaseWeapon::ACBaseWeapon()
{
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");
	CHelpers::CreateActorComponent<UCSkillManagement>(this, &SkillManagement, "SkillManagement");

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
}

// Called every frame
void ACBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACBaseWeapon::OnFire()
{
	SetupOwnerCharacter();
	if (!OwnerCharacter)
	{
		CLog::Log("OnFire() called but OwnerCharacter is null. Attempting to set it up.");
		if (!OwnerCharacter)
		{
			CLog::Log("Failed to set up OwnerCharacter. Cannot fire.");
			return;
		}
	}
}


void ACBaseWeapon::SetupOwnerCharacter()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}
