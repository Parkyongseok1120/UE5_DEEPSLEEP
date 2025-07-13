// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/CBaseCharacter.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"
#include "CPlayerCharacter.generated.h"

// 전방 선언
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
class UCInputConfig;
struct FInputActionValue;

UCLASS()
class DEEPSLEEPRENEW_API ACPlayerCharacter : public ACBaseCharacter
{
	GENERATED_BODY()

//=========================================================================================
// 함수 선언부
//=========================================================================================
public:
	// 생성자 및 기본 함수
	ACPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void AttackEnemy(ACBaseCharacter* Target) override;
	
	// 인라인 접근자
	FORCEINLINE UAnimMontage* GetFireAnimMontage() { return FireAnimMong; }
	FORCEINLINE UAnimMontage* GetReloadAnimMontage() { return ReloadAnimMong; }
	
	// 무기 관련 함수
	UFUNCTION()
	void SpawnHealthCore();
	
	UFUNCTION()
	void SpawnOblivionCore();
	
	UFUNCTION()
	void HideWeapon1();
	
	// 카메라 함수
	void BeginZoom();
	void EndZoom();
	
	// 입력 처리 함수
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

protected:
	// 기본 오버라이드 함수
	virtual void BeginPlay() override;
	virtual FVector GetPawnViewLocation() const override;
	
	// 상태 관련 함수
	UFUNCTION(BlueprintCallable, Category = "State")
	void OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType);
	
	UFUNCTION(BlueprintCallable, Category = "State")
	void OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType);

private:
	// 움직임 관련 함수
	void MoveForward(float Value);
	void MoveRight(float Value);
	void BeginSprint();
	void EndSprint();
	void OnWalk();
	void Jump();
	bool IsGrounded() const;
	
	// 대시 함수
	void DashStart();
	
	// 아이템 관련 함수
	void InteractWithItem(ACBaseItem* Item);
	void TryPickupItem();

//=========================================================================================
// 변수 선언부
//=========================================================================================
public:
	// 입력 설정
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UCInputConfig* InputConfig;
	
	// 카메라 회전 속도
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

protected:
	// 움직임 속도 설정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovementSpeed")
	float SprintingSpeed = 650.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovementSpeed")
	float WalkingSpeed = 250.0f;
	
	// 무기 애니메이션
	UPROPERTY(EditAnywhere, Category = "FireAnimMongtage")
	UAnimMontage* FireAnimMong;
	
	UPROPERTY(EditAnywhere, Category = "FireAnimMongtage")
	UAnimMontage* ReloadAnimMong;
	
	// 무기 관리 컴포넌트
	UPROPERTY(VisibleAnywhere)
	UCWeaponManagement* WeaponManagement;

private:
	// 컴포넌트
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCDashComponent* DashComponent;
	
	UPROPERTY(VisibleAnywhere)
	UCInventoryComponent* InventoryComponent;
	
	// 카메라 관련
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
	
	float DefaultFOV;
	
	// 움직임 관련 변수
	UPROPERTY(VisibleAnywhere)
	bool bisSprint;
	
	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpForce = 500.0f;
	
	UPROPERTY(EditAnywhere, Category = "Jump")
	int32 MaxJumpCount = 2;
	
	int32 CurrentJumpCount = 0;
	
	bool bCanDoubleJump;
	
	// 무기 관련
	ACCoreWeapon* CoreWeapon;
};