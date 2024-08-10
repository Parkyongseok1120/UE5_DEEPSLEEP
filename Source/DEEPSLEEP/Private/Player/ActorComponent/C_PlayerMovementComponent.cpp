// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_PlayerMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Util/Global.h"

// Sets default values for this component's properties
UC_PlayerMovementComponent::UC_PlayerMovementComponent()
{
	
}

void UC_PlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
}

void UC_PlayerMovementComponent::BeginSprint()
{
	bIsSprinting = true;
	SetSpeed(PlayerSpeed[2]);
}

void UC_PlayerMovementComponent::EndSprint()
{
	bIsSprinting = false;
	OnWalk();
}

void UC_PlayerMovementComponent::OnWalk()
{
	if(bIsSprinting == false)
	{
		SetSpeed(PlayerSpeed[1]);
	}
}

void UC_PlayerMovementComponent::SetSpeed(float Speed)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed;
}

void UC_PlayerMovementComponent::OnMoveForward(float InAxis)
{
	CheckFalse(bCanMove);

	
	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	OwnerCharacter->AddMovementInput(direction, InAxis);
}

void UC_PlayerMovementComponent::OnMoveRight(float InAxis)
{
	CheckFalse(bCanMove);

	FRotator rotator = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	OwnerCharacter->AddMovementInput(direction, InAxis);
}

void UC_PlayerMovementComponent::OnHorizontalLook(float InAxis)
{
	CheckTrue(bFixedCamera);

	OwnerCharacter->AddControllerYawInput(InAxis * HorizontalLook * GetWorld()->GetDeltaSeconds());
}

void UC_PlayerMovementComponent::OnVerticalLook(float InAxis)
{
	CheckTrue(bFixedCamera);

	OwnerCharacter->AddControllerPitchInput(InAxis * VerticalLook * GetWorld()->GetDeltaSeconds());
}

void UC_PlayerMovementComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
}

void UC_PlayerMovementComponent::DisableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UC_PlayerMovementComponent::Move()
{
	bCanMove = true;
}

void UC_PlayerMovementComponent::Stop()
{
	bCanMove = false;
}
