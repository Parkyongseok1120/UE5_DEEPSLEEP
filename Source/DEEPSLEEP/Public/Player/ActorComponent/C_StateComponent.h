// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_StateComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Default = 0, Jump, Dash, Max
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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMovementTypeChanged, EMovementState, InPrevType, EMovementState, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSelfStateTypeChanged, ESelfState, InPrevType, ESelfState, InNewType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeaponTypeChanged, EWeaponState, InPrevType, EWeaponState, InNewType);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_StateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsDefaultMode() { return MovementType == EMovementState::Default; }
	FORCEINLINE bool IsDeadMode() { return SelfStateType == ESelfState::Dead; }
	
public:	
	UC_StateComponent();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public: //--------------Movmemnt State--------
	void SetDefalutState();
	void SetJumpState();
	void DashState();

public: //--------------Self State--------
	void SetAliveState();
	void SetDeadState();
	void SetFaintState();
	

public: //--------------Weapon State--------
	void SetHandsState();
	void SetHealthCoreState();
	void SetOblivionCoreState();
	void SetUtilCoreState();


	
private://--------------Change Type----------
	void ChangeMovementType(EMovementState InType);
	void ChangeSelfStateType(ESelfState InType);
	void ChangeWeaponType(EWeaponState InType);
	

public: //Delegate
	FMovementTypeChanged OnMovementTypeChanged;
	FSelfStateTypeChanged OnSelfStateTypeChanged;
	FWeaponTypeChanged OnWeaponTypeChanged;
	 
private: //Enums
	EMovementState MovementType;
	ESelfState SelfStateType;
	EWeaponState WeaponType;

private:
	class AC_PlayerCharacter* OwnerCharacter;
	
};
