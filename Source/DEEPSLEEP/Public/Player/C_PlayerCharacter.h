// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActorComponent/C_StateComponent.h"
#include "C_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UC_DashComponent;
class UC_StateComponent;
class UC_TargetComponent;
class AC_DashGhost;
struct FInputActionValue;
class UC_InputComponent;
class AC_BaseWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDelegate);


UCLASS()
class DEEPSLEEP_API AC_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
 	AC_PlayerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual FVector GetPawnViewLocation() const override;


	//---------------Input---------------------------
private:
	UPROPERTY(VisibleAnywhere, Category = "input")
	UC_InputComponent* Input;

	//----------------Weapon-------------------------
private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AC_BaseWeapon* BaseWeapon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AC_BaseWeapon> BaseWeaponClass;
	
public:
	UFUNCTION()
	void SpawnWeapon1();
	
	UFUNCTION()
	void CallOnFire();
	


	
	//-----------------Camera------------------------------

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;

	UPROPERTY()
	bool bWantsToZoom;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV = 40.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Player", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed = 20.0f;

	//Default camera status value at game startup
	float DefaultFOV;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

public:
	void BeginZoom();
	void EndZoom();
	


	
	//-----------------Movement----------------------------
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovementSpeed")
	float SprintingSpeed = 650.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovementSpeed")
	float WalkingSpeed = 250.0f;

private:
	UPROPERTY(VisibleAnywhere)
	bool bisSprint;

	UPROPERTY(VisibleAnywhere)
	UC_DashComponent* DashComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AC_DashGhost> DashGhostClass;
	
	AC_DashGhost* DashGhost;
	
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginSprint();
	void EndSprint();
	void OnWalk();

public:
	UFUNCTION()
	void StartDashGhost();
	
	UFUNCTION()
	void EndDashGhost();
	
	FPlayerDelegate OnDashGhostEvent;
	

	
	
	//-----------------PlayerState----------------------------

private:
	UPROPERTY(VisibleAnywhere)
	UC_StateComponent* State;

	UFUNCTION()
	void P_OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType);
	
	UFUNCTION()
	void P_OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType);

	UFUNCTION()
	void P_OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType);

	UFUNCTION()
	void P_OnBattleTypeChanged(EBattleState InPrevType, EBattleState InNewType);


	//-----------------Target----------------------------
private:
	UPROPERTY(VisibleAnywhere)
	UC_TargetComponent* TargetComponent;
	
};
