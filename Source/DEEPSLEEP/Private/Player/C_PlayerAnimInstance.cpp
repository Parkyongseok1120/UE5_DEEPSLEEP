// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_PlayerAnimInstance.h"

#include "AudioMixerDevice.h"
#include "Util/Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/C_PlayerCharacter.h"

void UC_PlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(OwnerCharacter);
	
	PlayerCharacter = Cast<AC_PlayerCharacter>(this->TryGetPawnOwner());
	
}

void UC_PlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	EquipWeapon(bisEqiupWepaon);
	if(PlayerCharacter->GetbEquipWeapon() == true)
	{
		CLog::Print("true");
	}
	
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(OwnerCharacter);
	
	Speed = OwnerCharacter->GetVelocity().Size2D();
	FRotator rotator = OwnerCharacter->GetVelocity().ToOrientationRotator(); //현재 가는 벡터위치의 회전값을 구함.
	FRotator rotator2 = OwnerCharacter->GetControlRotation(); // 카메라의 회전방향
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2); // 두 회전값의 평균을 구함

	//// 이전 회전값.
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 100);
	Direction = PrevRotation.Yaw;
	
	if(Direction>= 170 && Direction<= -170) //Direction의 값이 170이상이거나 -170이하일 경우,
	{
		float NewDirection = FMath::Abs(Direction); //Direction을 절댓값으로 바꾸고 
		Direction = FMath::Lerp(Direction, NewDirection, DeltaSeconds * 4.0f);
		//Lerp 함수로 이전프레임의 Direction값과 현재 프레임의 Direction을 선형보간함.
	}
	
	bFalling = OwnerCharacter->GetCharacterMovement()->IsFalling();
}

bool UC_PlayerAnimInstance::EquipWeapon(bool B_EW)
{
	B_EW = PlayerCharacter->GetbEquipWeapon();
	if(B_EW == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}


