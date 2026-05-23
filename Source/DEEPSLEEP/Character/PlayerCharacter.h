// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/DEEPSLEEPCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UJetpackComponent;
class UDashComponent;
struct FInputActionValue;

/** ???, ?? ???, ???? ?? ?? ?? ??? ???? ?? ??? ?? ??????. */
UCLASS(Blueprintable)
class DEEPSLEEP_API APlayerCharacter : public ADEEPSLEEPCharacter
{
	GENERATED_BODY()

	/** ???? ??? ?? ???? ??? ? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** ?? ??? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	/** ??? ?? ???? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UJetpackComponent> JetpackComponent;

	/** ?? ?? ???? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDashComponent> DashComponent;

protected:
	/** ?? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	/** ?? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	/** ?? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	/** ??? ?? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MouseLookAction;

	/** ?? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> SprintAction;

	/** ???? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> CrouchAction;

	/** ?? ?? ?? */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> DashAction;

	/** ??? ??? ?? ??? ?? ?? ?? */
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector2D LastMoveInput;

public:
	APlayerCharacter();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void UpdateJetpackMoveThrust(float ForwardInput);
	void HandleStartSprinting();
	void HandleStopSprinting();
	void HandleStartCrouching();
	void HandleStopCrouching();

public:
	virtual void DoJumpStart() override;
	virtual void DoJumpEnd() override;

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoDash();

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UJetpackComponent* GetJetpackComponent() const { return JetpackComponent; }
	FORCEINLINE UDashComponent* GetDashComponent() const { return DashComponent; }
};

