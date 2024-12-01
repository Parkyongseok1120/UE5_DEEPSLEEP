// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

class ACBaseCharacter;

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

class ACBaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool IsDefaultMode() { return MovementType == EMovementState::Default; }
	FORCEINLINE bool IsDeadMode() { return SelfStateType == ESelfState::Dead; }
	
	// Sets default values for this component's properties
	UCStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
	UPROPERTY(VisibleAnywhere)
	ACBaseCharacter* OwnerCharacter;
	
		
};
