// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StateComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle = 0, Walk, Sprint, Jump, Dash, Max
};

UENUM(BlueprintType)
enum class ESelfState : uint8
{
	Alive = 0, Dead, Faint, Max
};

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Hands = 0, HealthCore, OblivionCore, UtilCore, Max
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	NoBattle = 0, Battle, TakeTargeting, Max
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
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: //--------------Movmemnt State--------
	void SetMovementState();

public: //--------------Self State--------
	void SetSelfState();

public: //--------------Weapon State--------
	void SetWeaponState();
	

public: //--------------Battle State--------
	void SetBattleState();


	
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
	EBattleState BattleType;
	EWeaponState WeaponType;

private:
	class AC_PlayerCharacter* OwnerCharacter;
	
};
