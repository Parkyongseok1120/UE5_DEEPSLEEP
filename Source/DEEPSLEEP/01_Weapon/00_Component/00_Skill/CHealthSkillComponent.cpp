// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/00_Component/00_Skill/CHealthSkillComponent.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"

#include "Global.h"

UCHealthSkillComponent::UCHealthSkillComponent()
{
}

void UCHealthSkillComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SetOwnerWeapon();
}

void UCHealthSkillComponent::SetOwnerWeapon()
{
	OwnerWeapon = Cast<ACCoreWeapon>(GetOwner());
}
