// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/CStateComponent.h"
#include "00_Character/CBaseCharacter.h"
#include "Global.h"


// Sets default values for this component's properties
UCStateComponent::UCStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACBaseCharacter>(GetOwner());
}

//-------------Movement-----------------
void UCStateComponent::SetDefalutState()
{
	ChangeMovementType(EMovementState::Default);
}

void UCStateComponent::SetJumpState()
{
	ChangeMovementType(EMovementState::Jump);
}

void UCStateComponent::DashState()
{
	ChangeMovementType(EMovementState::Dash);
}




//-------------SelfState-----------------
void UCStateComponent::SetAliveState()
{
	ChangeSelfStateType(ESelfState::Alive);
}

void UCStateComponent::SetDeadState()
{
	ChangeSelfStateType(ESelfState::Dead);
}

void UCStateComponent::SetFaintState()
{
	ChangeSelfStateType(ESelfState::Faint);
}





//-------------Weapons-----------------
void UCStateComponent::SetHandsState()
{
	ChangeWeaponType(EWeaponState::Hands);
}

void UCStateComponent::SetHealthCoreState()
{
	ChangeWeaponType(EWeaponState::HealthCore);
}

void UCStateComponent::SetOblivionCoreState()
{
	ChangeWeaponType(EWeaponState::OblivionCore);
}

void UCStateComponent::SetUtilCoreState()
{
	ChangeWeaponType(EWeaponState::UtilCore);
}



void UCStateComponent::ChangeMovementType(EMovementState InType)
{
	EMovementState prevType = MovementType;
	MovementType = InType;

	if (OnMovementTypeChanged.IsBound())
		OnMovementTypeChanged.Broadcast(prevType, InType);
}

void UCStateComponent::ChangeSelfStateType(ESelfState InType)
{
	ESelfState prevType = SelfStateType;
	SelfStateType = InType;

	if (OnSelfStateTypeChanged.IsBound())
		OnSelfStateTypeChanged.Broadcast(prevType, InType);
}

void UCStateComponent::ChangeWeaponType(EWeaponState InType)
{
	EWeaponState prevType = WeaponType;
	WeaponType = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(prevType, InType);
}






