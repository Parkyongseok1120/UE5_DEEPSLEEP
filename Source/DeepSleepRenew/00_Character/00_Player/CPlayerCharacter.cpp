// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/CPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "00_Character/02_Component/CDashComponent.h"
#include "00_Character/02_Component/CInventoryComponent.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "01_Weapon/CBaseWeapon.h"

#include "02_Item/CBaseItem.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Global.h"
#include "00_Character/CAnimInstance.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	CHelpers::CreateActorComponent<UCDashComponent>(this, &DashComponent, "Dash");
	CHelpers::CreateActorComponent<UCInventoryComponent>(this, &InventoryComponent, "Inventory");

	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &PlayerCamera, "Camera", SpringArm);
	GetMesh()->SetRelativeLocation(FVector(0,0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->SetRelativeLocation(FVector(-70,0,120));
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->bEnableCameraLag = true;
	bWantsToZoom = false;
	bisSprint = false;
	bCanDoubleJump = true;
}

void ACPlayerCharacter::DashStart()
{
	if(DashComponent)
		DashComponent->BeginDash();
	else
	{
		CLog::Print("DashComponent nullptr");
	}
}

void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultFOV = PlayerCamera->FieldOfView;
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

	StateComponent->OnMovementTypeChanged.AddDynamic(this, &ACPlayerCharacter::OnMovementTypeChanged);
	StateComponent->OnWeaponTypeChanged.AddDynamic(this, &ACPlayerCharacter::OnWeaponTypeChanged);

	Weapon = Cast<ACBaseWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), ACBaseWeapon::StaticClass()));


}

void ACPlayerCharacter::SpawnWeapon1()
{
	StateComponent->SetHealthCoreState();
}

void ACPlayerCharacter::HideWeapon1()
{
	StateComponent->SetHandsState();
	bEquipWeapon = false;
}

void ACPlayerCharacter::CallOnFire()
{
	if (Weapon != nullptr && bEquipWeapon == true)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if(AnimInstance && FireAnimMong)
		{
			AnimInstance->Montage_Play(FireAnimMong);
			Weapon->OnFire(); // OtherActor의 함수 호출
		}
	}
	else
	{
		CLog::Print("Weapon Nullptr");
	}

}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;

	//CurrentFOV : Current field of view
	float NewFOV = FMath::FInterpTo(PlayerCamera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
	// 스폰된 액터가 있다면
	PlayerCamera->SetFieldOfView(NewFOV);
}

FVector ACPlayerCharacter::GetPawnViewLocation() const
{
	if (PlayerCamera)
	{
		return PlayerCamera->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jumping", IE_Pressed, this, &ACPlayerCharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACPlayerCharacter::AddControllerYawInput);
	

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayerCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayerCharacter::EndSprint);
	PlayerInputComponent->BindAction("C_Key", IE_Pressed, this, &ACPlayerCharacter::DashStart);
	PlayerInputComponent->BindAction("Key_1",IE_Pressed, this, &ACPlayerCharacter::HideWeapon1);
	PlayerInputComponent->BindAction("Key_2",IE_Pressed, this, &ACPlayerCharacter::SpawnWeapon1);
	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &ACPlayerCharacter::CallOnFire);
	
		
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &ACPlayerCharacter::BeginZoom);
	PlayerInputComponent->BindAction("MouseRight", IE_Released, this, &ACPlayerCharacter::EndZoom);
}

void ACPlayerCharacter::AttackEnemy(ACBaseCharacter* Target)
{
	Super::AttackEnemy(Target);
	if (Target)
	{
		// 플레이어가 공격을 하면 Target 에 데미지를 입힘
		UE_LOG(LogTemp, Warning, TEXT("Player attacks!"));
		//Target->TakeDamage(20); // 예시로 20 데미지
	}

}

void ACPlayerCharacter::BeginZoom()
{
	if(bisSprint == true)
		EndSprint();
	
	bWantsToZoom = true;
	SpringArm->bEnableCameraLag = false;
	
}

void ACPlayerCharacter::EndZoom()
{
	bWantsToZoom = false;
	SpringArm->bEnableCameraLag = true;
}

void ACPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void ACPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector() * Value);
	}
}

void ACPlayerCharacter::BeginSprint()
{
	if(bWantsToZoom == false)
	{
		bisSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
}

void ACPlayerCharacter::EndSprint()
{
	bisSprint = false;
	OnWalk();
}

void ACPlayerCharacter::OnWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}


void ACPlayerCharacter::InteractWithItem(ACBaseItem* Item)
{
	if (Item || ACBaseItem::StaticClass())
	{
		// 아이템의 정보를 가져와 인벤토리에 추가
		InventoryComponent->AddItem(Item->GetItemInfo());

		// 아이템을 주운 후 액터에서 처리 (예: 파괴)
		Item->OnPickedUp();
	}
}

void ACPlayerCharacter::TryPickupItem()
{
	// 레이캐스트를 통해 플레이어 앞의 아이템을 찾음
	FHitResult HitResult;
	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start + (ForwardVector * 200.0f); // 200 유닛 거리 내에 있는 액터 찾기

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		// 아이템 액터를 찾으면 상호작용 실행
		ACBaseItem* HitItem = Cast<ACBaseItem>(HitResult.GetActor());
	
		if (HitItem)
		{
			InteractWithItem(HitItem);
		}
	}
}

void ACPlayerCharacter::OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType)
{
}

void ACPlayerCharacter::OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType)
{
}

void ACPlayerCharacter::OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType)
{
	switch(InNewType)
	{
	case EWeaponState::Hands:
		{
			if(Weapon != nullptr)
			{
				Weapon -> SetActorHiddenInGame(true);
				Weapon -> SetActorEnableCollision(false);
				Weapon -> SetActorTickEnabled(false);
			}
		}
	case EWeaponState::HealthCore:
		{
			if(bSpawnWeapon == true)
			{
				Weapon->SetActorHiddenInGame(false);
				Weapon->SetActorEnableCollision(true);
				Weapon->SetActorTickEnabled(true);
				bEquipWeapon = true;

			}
			else if (Weapon == nullptr)
			{
				bEquipWeapon = true;
				bSpawnWeapon = true;
				Weapon = GetWorld()->SpawnActor<ACBaseWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
				if(Weapon)
				{
					Weapon->SetOwner(this);
					Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "Hard_r");
				}
			}
		}
	}
}

bool ACPlayerCharacter::IsGrounded() const
{
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 100.0f);  // 발 아래 100 유닛까지 체크

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);  // 자기 자신은 무시

	// Line Trace 실행
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,  // 또는 커스텀 트레이스 채널
		QueryParams
	);

	// 디버그 표시 (개발 중에 유용)
	DrawDebugLine(
		GetWorld(),
		Start,
		End,
		FColor::Red,
		false,
		1.0f,
		0,
		1.0f
	);
	return bHit;
}


void ACPlayerCharacter::Jump()
{
// 첫 번째 점프
	Super::Jump();
	if (IsGrounded() != true && bCanDoubleJump == true)
	{
		// 더블 점프
		LaunchCharacter(FVector(0.0f, 0.0f, JumpForce), false, true);
		bCanDoubleJump = false;
	}
	
	if(IsGrounded() == true)
	{
		bCanDoubleJump = true;
	}
}