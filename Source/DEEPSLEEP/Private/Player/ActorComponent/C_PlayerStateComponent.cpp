// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/ActorComponent/C_StateComponent.h"

UC_StateComponent::UC_StateComponent()
{
	
}

void UC_StateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

//---------------------Movement Type--------------

void UC_StateComponent::SetIdleMode()
{
	ChangeMovementType(EMovementState::Idle);
}

void UC_StateComponent::SetWalkMode()
{
	ChangeMovementType(EMovementState::Walk);
}

void UC_StateComponent::SetSprintMode()
{
	ChangeMovementType(EMovementState::Sprint);
}

void UC_StateComponent::SetJumpMode()
{
	ChangeMovementType(EMovementState::Jump);
}

void UC_StateComponent::SetDashMode()
{
	ChangeMovementType(EMovementState::Dash);
}




//---------------------SelfState Type--------------

void UC_StateComponent::SetAliveMode()
{
	ChangeSelfStateType(ESelfState::Alive);
}

void UC_StateComponent::SetDeadMode()
{
	ChangeSelfStateType(ESelfState::Dead);
}

void UC_StateComponent::SetFaintMode()
{
	ChangeSelfStateType(ESelfState::Faint);
}




//---------------------Weapon Type--------------
void UC_StateComponent::SetHandsMode()
{
	ChangeWeaponType(EWeaponState::Hands);
}

void UC_StateComponent::SetHealthCoreMode()
{
	ChangeWeaponType(EWeaponState::HealthCore);
}

void UC_StateComponent::SetOblivionCoreMode()
{
	ChangeWeaponType(EWeaponState::OblivionCore);
}

void UC_StateComponent::SetUtilCoreMode()
{
	ChangeWeaponType(EWeaponState::UtilCore);
}



//---------------------Battle Type--------------

void UC_StateComponent::SetNoBattleMode()
{
	ChangeBattleType(EBattleState::NoBattle);
}

void UC_StateComponent::SetBattleMode()
{
	ChangeBattleType(EBattleState::Battle);
}

void UC_StateComponent::SetTakeTargetingMode()
{
	ChangeBattleType(EBattleState::TakeTargeting);
}




//---------------------ChangeStateType--------------

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

void UC_StateComponent::ChangeBattleType(EBattleState InType)
{
	EBattleState prevType = BattleType;
	BattleType = InType;

	if (OnBattleTypeChanged.IsBound())
		OnBattleTypeChanged.Broadcast(prevType, InType);
}




