// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StateComponent.generated.h"

UENUM()
enum EMovementState : uint8
{
	Idle = 0,
	Walk,
	Sprint,
	Jump,
	Dash
};

UENUM()
enum ESelfState : uint8
{
	Alive = 0,
	Dead,
	Faint
};

UENUM()
enum EWeaponState : uint8
{
	Hands = 0,
	HealthCore,
	OblivionCore,
	UtilCore
};

UENUM()
enum EBattleState : uint8
{
	NoBattle = 0,
	Battle,
	TakeTargeting
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMovementTypeChanged, EMovementState, InPrevType, EMovementState, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelfStateTypeChanged, ESelfState, InPrevType, ESelfState, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponState, InPrevType, EWeaponState, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBattleTypeChanged, EBattleState, InPrevType, EBattleState, InNewType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsIdleMode() { return MovementType == EMovementState::Idle; }
	FORCEINLINE bool IsDeadMode() { return SelfStateType == ESelfState::Dead; }
	
public:	
	UC_StateComponent();

protected:
	virtual void BeginPlay() override;

public: //--------------Movmemnt State--------
	void SetIdleMode();
	void SetWalkMode();
	void SetSprintMode();
	void SetJumpMode();
	void SetDashMode();

public: //--------------Self State--------
	void SetAliveMode();
	void SetDeadMode();
	void SetFaintMode();

public: //--------------Weapon State--------
	void SetHandsMode();
	void SetHealthCoreMode();
	void SetOblivionCoreMode();
	void SetUtilCoreMode();

public: //--------------Battle State--------
	void SetNoBattleMode();
	void SetBattleMode();
	void SetTakeTargetingMode();


	
private://--------------Change Type----------
	void ChangeMovementType(EMovementState InType);
	void ChangeSelfStateType(ESelfState InType);
	void ChangeWeaponType(EWeaponState InType);
	void ChangeBattleType(EBattleState InType);

public: //Delegate
	FMovementTypeChanged OnMovementTypeChanged;
	FSelfStateTypeChanged OnSelfStateTypeChanged;
	FWeaponTypeChanged OnWeaponTypeChanged;
	FBattleTypeChanged OnBattleTypeChanged;

private: //Enums
	EMovementState MovementType;
	ESelfState SelfStateType;
	EWeaponState WeaponType;
	EBattleState BattleType;
};
