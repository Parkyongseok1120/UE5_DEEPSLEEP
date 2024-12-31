// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/CBaseCharacter.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"
#include "CPlayerCharacter.generated.h"

class ACCoreWeapon;
class UCInputComponent;
class UCDashComponent;
class UCHealthComponent;
class UCStateComponent;
class UCInventoryComponent;
class UCTargetComponent;
class USkeletalMeshComponent;
class UCWeaponManagement;
class UAnimMontage;
class UParticleSystem;
class ACBaseItem;
class ACBaseWeapon;

UCLASS()
class DEEPSLEEPRENEW_API ACPlayerCharacter : public ACBaseCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();

	FORCEINLINE UAnimMontage* GetAnimMontage(){return FireAnimMong;}

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCDashComponent* DashComponent;

	void DashStart();
	
	//-----------------Camera------------------------------

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

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
	
	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpForce = 500.0f;

	UPROPERTY(EditAnywhere, Category = "Jump")
	int32 MaxJumpCount = 2;

	int32 CurrentJumpCount = 0;
	
	bool bCanDoubleJump;
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginSprint();
	void EndSprint();
	void OnWalk();
	void Jump();
	bool IsGrounded()const;


	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual FVector GetPawnViewLocation() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void AttackEnemy(ACBaseCharacter* Target) override;



	//------item

private:
	UPROPERTY(VisibleAnywhere)
	UCInventoryComponent* InventoryComponent;

	void InteractWithItem(ACBaseItem* Item);
	void TryPickupItem();


	//-----State
	
	UFUNCTION(BlueprintCallable, Category = "State")
	void OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType);
	
	UFUNCTION(BlueprintCallable, Category = "State")
	void OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType);

	//UFUNCTION(BlueprintCallable, Category = "State")
	//void OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType);
	
	//-----Weapon;
	UPROPERTY()
	ACBaseWeapon* BaseWeapon;
	
	UPROPERTY(VisibleAnywhere)
	UCWeaponManagement* WeaponManagement;

protected:
	UPROPERTY(EditAnywhere,Category = "FireAnimMongtage")
	UAnimMontage* FireAnimMong;	


public:
	UFUNCTION()
	void SpawnHealthCore();
	
	UFUNCTION()
	void SpawnOblivionCore();

	UFUNCTION()
	void HideWeapon1();
	
	
	
	
};
