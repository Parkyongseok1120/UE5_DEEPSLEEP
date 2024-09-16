// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ActorComponent/C_StateComponent.h"
#include "Player/C_PlayerCharacter.h"
#include "Util/Global.h"

UC_StateComponent::UC_StateComponent()
{
	
}

void UC_StateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<AC_PlayerCharacter>(GetOwner());
	
}
void UC_StateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_StateComponent::SetMovementState()
{
}

void UC_StateComponent::SetSelfState()
{
}

void UC_StateComponent::SetWeaponState()
{
	ChangeWeaponType(EWeaponState::HealthCore);
}

void UC_StateComponent::SetBattleState()
{
	
}

void UC_StateComponent::ChangeMovementType(EMovementState InType)
{
	
}

void UC_StateComponent::ChangeSelfStateType(ESelfState InType)
{
}

void UC_StateComponent::ChangeWeaponType(EWeaponState InType)
{
	EWeaponState prevType = WeaponType;
	WeaponType = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(prevType, InType);
}

void UC_StateComponent::ChangeBattleType(EBattleState InType)
{
}






