// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/CAnimInstance.h"

#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "00_Player/CPlayerCharacter.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	PlayerCharacter = Cast<ACPlayerCharacter>(TryGetPawnOwner());
	CheckNull(PlayerCharacter)
	//State = CHelpers::GetComponent<UC_StateComponent>(PlayerCharacter);
	//if (!!State)
	//	State->OnWeaponTypeChanged.AddDynamic(this, &UC_PlayerAnimInstance::OnWeaponTypeChanged);
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	
	Super::NativeUpdateAnimation(DeltaSeconds);
	CheckNull(PlayerCharacter);
	
	C_Speed = PlayerCharacter->GetVelocity().Size2D();
	FRotator rotator = PlayerCharacter->GetVelocity().ToOrientationRotator(); //현재 가는 벡터위치의 회전값을 구함.
	FRotator rotator2 = PlayerCharacter->GetControlRotation(); // 카메라의 회전방향
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(rotator, rotator2); // 두 회전값의 평균을 구함

	//// 이전 회전값.
	PrevRotation = UKismetMathLibrary::RInterpTo(PrevRotation, delta, DeltaSeconds, 100);
	C_Direction = PrevRotation.Yaw;
	
	if(C_Direction >= 170 && C_Direction <= -170) //Direction의 값이 170이상이거나 -170이하일 경우,
	{
		float NewDirection = FMath::Abs(C_Direction); //Direction을 절댓값으로 바꾸고 
		C_Direction = FMath::Lerp(C_Direction, NewDirection, DeltaSeconds * 4.0f);
		//Lerp 함수로 이전프레임의 Direction값과 현재 프레임의 Direction을 선형보간함.
	}
	
	bFalling = PlayerCharacter->GetCharacterMovement()->IsFalling();
}
