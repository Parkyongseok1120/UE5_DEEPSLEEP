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




//-------------Movement-----------------
void UC_StateComponent::SetDefalutState()
{
	ChangeMovementType(EMovementState::Default);
}

void UC_StateComponent::SetJumpState()
{
	ChangeMovementType(EMovementState::Jump);
}

void UC_StateComponent::DashState()
{
	ChangeMovementType(EMovementState::Dash);
}




//-------------SelfState-----------------
void UC_StateComponent::SetAliveState()
{
	ChangeSelfStateType(ESelfState::Alive);
}

void UC_StateComponent::SetDeadState()
{
	ChangeSelfStateType(ESelfState::Dead);
}

void UC_StateComponent::SetFaintState()
{
	ChangeSelfStateType(ESelfState::Faint);
}





//-------------Weapons-----------------
void UC_StateComponent::SetHandsState()
{
	ChangeWeaponType(EWeaponState::Hands);
}

void UC_StateComponent::SetHealthCoreState()
{
	ChangeWeaponType(EWeaponState::HealthCore);
}

void UC_StateComponent::SetOblivionCoreState()
{
	ChangeWeaponType(EWeaponState::OblivionCore);
}

void UC_StateComponent::SetUtilCoreState()
{
	ChangeWeaponType(EWeaponState::UtilCore);

}



void UC_StateComponent::ChangeMovementType(EMovementState InType)
{
	EMovementState prevType = MovementType;
	MovementType = InType;

	if (OnMovementTypeChanged.IsBound())
		OnMovementTypeChanged.Broadcast(prevType, InType);
}

void UC_StateComponent::ChangeSelfStateType(ESelfState InType)
{
	ESelfState prevType = SelfStateType;
	SelfStateType = InType;

	if (OnSelfStateTypeChanged.IsBound())
		OnSelfStateTypeChanged.Broadcast(prevType, InType);
}

void UC_StateComponent::ChangeWeaponType(EWeaponState InType)
{
	EWeaponState prevType = WeaponType;
	WeaponType = InType;

	if (OnWeaponTypeChanged.IsBound())
		OnWeaponTypeChanged.Broadcast(prevType, InType);
}






