// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_PlayerCharacter.h"
#include "Player/C_DashGhost.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ActorComponent/C_DashComponent.h"
#include "Player/ActorComponent/C_TargetComponent.h"
#include "Player/ActorComponent/C_InputComponent.h"
#include "Player/Weapons/C_BaseWeapon.h"
#include "Util/Global.h"

AC_PlayerCharacter::AC_PlayerCharacter()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &PlayerCamera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UC_DashComponent>(this, &DashComponent, "Dash");
	CHelpers::CreateActorComponent<UC_StateComponent>(this, &State, "State");
	CHelpers::CreateActorComponent<UC_TargetComponent>(this, &TargetComponent, "Target");
	CHelpers::CreateActorComponent<UC_InputComponent>(this, &Input, "Input");
	CHelpers::CreateActorComponent<UC_HealthComponent>(this, &HealthComponent, "Health");
	
	GetMesh()->SetRelativeLocation(FVector(0,0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm->bEnableCameraLag = true;
	bWantsToZoom = false;
	bisSprint = false;
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultFOV = PlayerCamera->FieldOfView;

	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;


	//Player State
	State->OnMovementTypeChanged.AddDynamic(this, &AC_PlayerCharacter::OnMovementTypeChanged);
	State->OnSelfStateTypeChanged.AddDynamic(this, &AC_PlayerCharacter::OnSelfStateTypeChanged);
	State->OnWeaponTypeChanged.AddDynamic(this, &AC_PlayerCharacter::OnWeaponTypeChanged);

	BaseWeapon = Cast<AC_BaseWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), AC_BaseWeapon::StaticClass()));
}

void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;

	//CurrentFOV : Current field of view
	float NewFOV = FMath::FInterpTo(PlayerCamera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	PlayerCamera->SetFieldOfView(NewFOV);
	
}

void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//--------------------------------KeyBoard----------------------------------------
	
	// Bind jump events
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AC_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AC_PlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AC_PlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AC_PlayerCharacter::AddControllerYawInput);

	
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AC_PlayerCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AC_PlayerCharacter::EndSprint);
	
	
	PlayerInputComponent->BindAction("MouseRight", IE_Pressed, this, &AC_PlayerCharacter::BeginZoom);
	PlayerInputComponent->BindAction("MouseRight", IE_Released, this, &AC_PlayerCharacter::EndZoom);

	PlayerInputComponent->BindAction("MouseLeft", IE_Pressed, this, &AC_PlayerCharacter::CallOnFire);
	PlayerInputComponent->BindAction("T_Key",IE_Pressed, Input, &UC_InputComponent::T_key);
	PlayerInputComponent->BindAction("C_Key",IE_Pressed, Input, &UC_InputComponent::C_key);
	PlayerInputComponent->BindAction("R_Key",IE_Pressed, Input, &UC_InputComponent::R_key);
	PlayerInputComponent->BindAction("Key_1",IE_Pressed, Input, &UC_InputComponent::key_1);
	PlayerInputComponent->BindAction("Key_2",IE_Pressed, Input, &UC_InputComponent::key_2);


	//--------------------------------KeyBoard----------------------------------------
}


//-----------------Camera------------------------------

FVector AC_PlayerCharacter::GetPawnViewLocation() const
{
	if (PlayerCamera)
	{
		return PlayerCamera->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

void AC_PlayerCharacter::CallOnFire()
{
	if (BaseWeapon)
	{
		BaseWeapon->OnFire(); // OtherActor의 함수 호출
	}
}
void AC_PlayerCharacter::SpawnWeapon1()
{
	if(bSpawnWeapon == true)
	{
		State->SetHealthCoreState();
		BaseWeapon->SetActorHiddenInGame(false);
		BaseWeapon->SetActorEnableCollision(true);
		BaseWeapon->SetActorTickEnabled(true);
	}
	else if (BaseWeapon == nullptr && BaseWeaponClass != nullptr)
	{
		if(State!=nullptr)
		{
			//UC_StateComponent 클래스의 SetWeaponState를 호출하여 Enum 값 변경.
			State->SetHealthCoreState();
			bEquipWeapon = true;
			bSpawnWeapon = true;
			BaseWeapon = GetWorld()->SpawnActor<AC_BaseWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
			if(BaseWeapon)
			{
				BaseWeapon->SetOwner(this);
				BaseWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHandSocket");
			}
		}
	}
}

void AC_PlayerCharacter::HideWeapon1()
{
	if(BaseWeapon != nullptr)
		if(State!=nullptr)
		{
			State->SetHandsState();
			bEquipWeapon = false;
			BaseWeapon -> SetActorHiddenInGame(true);
			BaseWeapon -> SetActorEnableCollision(false);
			BaseWeapon -> SetActorTickEnabled(false);
		}
}

void AC_PlayerCharacter::SwitchToWeapon()
{
	// 현재 무기 숨기기
	HideWeapon1();
    
	// 새 무기가 이미 생성되어 있는지 확인
	
}


void AC_PlayerCharacter::BeginZoom()
{
	if(bisSprint == true)
		EndSprint();
	
	bWantsToZoom = true;
	SpringArm->bEnableCameraLag = false;
	
}

void AC_PlayerCharacter::EndZoom()
{
	bWantsToZoom = false;
	SpringArm->bEnableCameraLag = true;
}







//-----------------Movement----------------------------

void AC_PlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void AC_PlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector() * Value);
	}
}

void AC_PlayerCharacter::BeginSprint()
{
	if(bWantsToZoom == false)
	{
		bisSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
}

void AC_PlayerCharacter::EndSprint()
{
	bisSprint = false;
	OnWalk();
}

void AC_PlayerCharacter::OnWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void AC_PlayerCharacter::StartDashGhost()
{
	//OnDashGhostEvent.Broadcast();
	
	if(!!DashGhostClass)
	{
		FVector location = this->GetActorLocation();
		location.Z -= this->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		FActorSpawnParameters params;
		params.Owner = this;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FTransform transform;
		transform.SetTranslation(location);

		DashGhost = this->GetWorld()->SpawnActor<AC_DashGhost>(DashGhostClass, transform,params);
	}
}

void AC_PlayerCharacter::EndDashGhost()
{
   if(!!DashGhost)
   		DashGhost->Destroy();
	
}






//-----------------Player State----------------------------

void AC_PlayerCharacter::OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType)
{
}

void AC_PlayerCharacter::OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType)
{
}

void AC_PlayerCharacter::OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType)
{
	/*switch (InNewType)
	{
	case EWeaponState::Hands:
		{
			InPrevType = EWeaponState::Hands;
			break;
		}
	case EWeaponState::HealthCore:
		{
			InPrevType = EWeaponState::Hands;
			break;
		}
	case EWeaponState::OblivionCore:
		{
			InPrevType = EWeaponState::Hands;
			break;
		}
	case EWeaponState::UtilCore:
		{
			InPrevType = EWeaponState::Hands;
			break;
		}
	case EWeaponState::Max:
		{
			InPrevType = EWeaponState::Hands;
			break;
		}
	}*/
}



