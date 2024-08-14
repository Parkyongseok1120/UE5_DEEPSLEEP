// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_PlayerAnimInstance.h"
#include "Util/Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/C_PlayerCharacter.h"

void UC_PlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	
}

void UC_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);
	
	Speed = OwnerCharacter->GetVelocity().Size2D();
	FRotator yawDirection = UKismetMathLibrary::MakeRotator(0,0,OwnerCharacter->GetControlRotation().Yaw);
	Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), yawDirection);
	bFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
}




