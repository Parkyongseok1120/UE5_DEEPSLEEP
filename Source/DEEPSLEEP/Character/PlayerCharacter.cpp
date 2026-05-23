// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "DashComponent.h"
#include "DEEPSLEEP.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "JetpackComponent.h"

APlayerCharacter::APlayerCharacter()
	: LastMoveInput(FVector2D::ZeroVector)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	JetpackComponent = CreateDefaultSubobject<UJetpackComponent>(TEXT("JetpackComponent"));
	DashComponent = CreateDefaultSubobject<UDashComponent>(TEXT("DashComponent"));
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerCharacter::DoJumpStart);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::DoJumpEnd);
		}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::Move);
		}

		if (MouseLookAction)
		{
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}

		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleStartSprinting);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::HandleStopSprinting);
		}

		if (CrouchAction)
		{
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::HandleStartCrouching);
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::HandleStopCrouching);
		}

		if (DashAction)
		{
			EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::DoDash);
		}
	}
	else
	{
		UE_LOG(LogDEEPSLEEP, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	LastMoveInput = MovementVector;

	DoMove(MovementVector.X, MovementVector.Y);
	UpdateJetpackMoveThrust(MovementVector.Y);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APlayerCharacter::UpdateJetpackMoveThrust(float ForwardInput)
{
	if (JetpackComponent)
	{
		JetpackComponent->ActivateThrust(ForwardInput > KINDA_SMALL_NUMBER, JetpackComponent->IsThrustingUp());
	}
}

void APlayerCharacter::HandleStartSprinting()
{
	StartSprinting();
}

void APlayerCharacter::HandleStopSprinting()
{
	StopSprinting();
}

void APlayerCharacter::HandleStartCrouching()
{
	Crouch();
}

void APlayerCharacter::HandleStopCrouching()
{
	UnCrouch();
}

void APlayerCharacter::DoJumpStart()
{
	Super::DoJumpStart();

	if (JetpackComponent)
	{
		JetpackComponent->ActivateThrust(JetpackComponent->IsThrustingForward(), true);
	}
}

void APlayerCharacter::DoJumpEnd()
{
	Super::DoJumpEnd();

	if (JetpackComponent)
	{
		JetpackComponent->ActivateThrust(JetpackComponent->IsThrustingForward(), false);
	}
}

void APlayerCharacter::DoDash()
{
	if (!DashComponent || !GetController())
	{
		return;
	}

	const FRotator ControlRotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector DashDirection = (ForwardDirection * LastMoveInput.Y) + (RightDirection * LastMoveInput.X);

	if (JetpackComponent)
	{
		JetpackComponent->ActivateThrust(false, false);
	}

	DashComponent->TryDash(DashDirection);
}

