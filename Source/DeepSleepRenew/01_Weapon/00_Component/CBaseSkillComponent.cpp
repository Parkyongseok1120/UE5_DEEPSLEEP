// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/00_Component/CBaseSkillComponent.h"
#include "01_Weapon/CBaseWeapon.h"
#include "CSkillManagement.h"
#include "00_Character/02_Component/CStateComponent.h"

#include "GameFramework/Actor.h"

#include "Global.h"

UCBaseSkillComponent::UCBaseSkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCBaseSkillComponent::BeginPlay()
{
	Super::BeginPlay();
	SetOwnerWeapon();
	GetOwnerComponent();
}

void UCBaseSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCBaseSkillComponent::SetOwnerWeapon()
{
	OwnerWeapon = Cast<ACBaseWeapon>(GetOwner());
}

void UCBaseSkillComponent::GetOwnerComponent()
{
	PlayerStateComponent = GetOwner()->FindComponentByClass<UCStateComponent>();
	SkillManagement = GetOwner()->FindComponentByClass<UCSkillManagement>();
}

