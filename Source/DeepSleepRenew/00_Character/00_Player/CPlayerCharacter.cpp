// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/02_Component/CDashComponent.h"
#include "00_Character/02_Component/CInventoryComponent.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "00_Character/CAnimInstance.h"
#include "00_Character/02_Component/CEnhancedInputComponent.h"
#include "00_Character/02_Component/CGameplayTags.h"

#include "02_Item/CBaseItem.h"
#include "01_Weapon/00_Component/CWeaponManagement.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"

#include "EnhancedInput/Public/InputAction.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Global.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	CHelpers::CreateActorComponent<UCDashComponent>(this, &DashComponent, "Dash");
	CHelpers::CreateActorComponent<UCInventoryComponent>(this, &InventoryComponent, "Inventory");
	CHelpers::CreateActorComponent<UCWeaponManagement>(this, &WeaponManagement, "WeaponManagement");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	SpringArm->SetRelativeRotation(FRotator(0, 0, 0));
	SpringArm->SetRelativeLocation(FVector(-18, 63, 49));

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bWantsToZoom = false;
	bisSprint = false;
	bCanDoubleJump = true;
}

void ACPlayerCharacter::DashStart()
{
	if (DashComponent)
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
	SpringArm->bEnableCameraLag = true;

	HideWeapon1();
}

void ACPlayerCharacter::SpawnHealthCore()
{
	StateComponent->SetHealthCoreState();
}

void ACPlayerCharacter::SpawnOblivionCore()
{
	StateComponent->SetOblivionCoreState();
}

void ACPlayerCharacter::HideWeapon1()
{
	StateComponent->SetHandsState();
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

	UCEnhancedInputComponent* CEnhancedInputComponent = Cast<UCEnhancedInputComponent>(PlayerInputComponent);
	check(CEnhancedInputComponent);

	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Input_Move);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Input_Look);

	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Mouse_Left, ETriggerEvent::Started, WeaponManagement, &UCWeaponManagement::PlayerAtteck);

	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Mouse_Right, ETriggerEvent::Started, this, &ACPlayerCharacter::BeginZoom);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Mouse_Right, ETriggerEvent::Completed, this, &ACPlayerCharacter::EndZoom);

	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Jump, ETriggerEvent::Started, this, &ACPlayerCharacter::Jump);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Sprint, ETriggerEvent::Started, this, &ACPlayerCharacter::BeginSprint);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Sprint, ETriggerEvent::Completed, this, &ACPlayerCharacter::EndSprint);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_1, ETriggerEvent::Started, this, &ACPlayerCharacter::HideWeapon1);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_2, ETriggerEvent::Started, this, &ACPlayerCharacter::SpawnHealthCore);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_3, ETriggerEvent::Started, this, &ACPlayerCharacter::SpawnOblivionCore);
	CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_C, ETriggerEvent::Started, this, &ACPlayerCharacter::DashStart);


	// Bind jump events
	//PlayerInputComponent->BindAction("Jumping", IE_Pressed, this, &ACPlayerCharacter::Jump);
	//PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayerCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayerCharacter::MoveRight);
	//PlayerInputComponent->BindAxis("LookUp", this, &ACPlayerCharacter::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("Turn", this, &ACPlayerCharacter::AddControllerYawInput);
	//
	//
	//PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayerCharacter::BeginSprint);
	//PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayerCharacter::EndSprint);
	//PlayerInputComponent->BindAction("C_Key", IE_Pressed, this, &ACPlayerCharacter::DashStart);
	//PlayerInputComponent->BindAction("Key_1",IE_Pressed, this, &ACPlayerCharacter::HideWeapon1);
	//PlayerInputComponent->BindAction("Key_2",IE_Pressed, this, &ACPlayerCharacter::SpawnHealthCore);
	//PlayerInputComponent->BindAction("Key_3",IE_Pressed, this, &ACPlayerCharacter::SpawnOblivionCore);
	//
	//PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, WeaponManagement, &UCWeaponManagement::PlayerAtteck);
	//
	//	
	//PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &ACPlayerCharacter::BeginZoom);
	//PlayerInputComponent->BindAction("MouseRight", IE_Released, this, &ACPlayerCharacter::EndZoom);
}

void ACPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	// input is a Vector2D
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X / 5);
		AddControllerPitchInput(LookAxisVector.Y / 5);
	}
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
	if (bisSprint == true)
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
	if (Value != 0.0f && Controller != nullptr)
	{

		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void ACPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && Controller != nullptr)
	{
		// 카메라의 rotation을 기준으로 right 방향 계산
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ACPlayerCharacter::BeginSprint()
{
	if (bWantsToZoom == false)
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

	if (IsGrounded() == true)
	{
		bCanDoubleJump = true;
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






