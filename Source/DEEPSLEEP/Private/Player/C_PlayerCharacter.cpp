// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_PlayerCharacter.h"
#include "Player/C_DashGhost.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ActorComponent/C_DashComponent.h"
#include "Util/Global.h"

AC_PlayerCharacter::AC_PlayerCharacter()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &PlayerCamera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UC_DashComponent>(this, &DashComponent, "Dash");
	CHelpers::CreateActorComponent<UC_StateComponent>(this, &State, "State");
	
	GetMesh()->SetRelativeLocation(FVector(0,0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

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
	State->OnMovementTypeChanged.AddDynamic(this, &AC_PlayerCharacter::P_OnMovementTypeChanged);
	State->OnSelfStateTypeChanged.AddDynamic(this, &AC_PlayerCharacter::P_OnSelfStateTypeChanged);
	State->OnWeaponTypeChanged.AddDynamic(this, &AC_PlayerCharacter::P_OnWeaponTypeChanged);
	State->OnBattleTypeChanged.AddDynamic(this, &AC_PlayerCharacter::P_OnBattleTypeChanged);
	
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
	
	
	PlayerInputComponent->BindAction("CameraZoom", IE_Pressed, this, &AC_PlayerCharacter::BeginZoom);
	PlayerInputComponent->BindAction("CameraZoom", IE_Released, this, &AC_PlayerCharacter::EndZoom);

	PlayerInputComponent->BindAction("Dash",IE_Pressed, DashComponent, &UC_DashComponent::BeginDash);

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
//	if(!!DashGhost)
	//{
	//	DashGhost->Destroy();
	//}
}


//-----------------Player State----------------------------

void AC_PlayerCharacter::P_OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType)
{
	//switch (InNewType)
	//{
	//	case EMovementState::Idle :
		 
	//	break;
	//}
}

void AC_PlayerCharacter::P_OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType)
{
}

void AC_PlayerCharacter::P_OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType)
{
}

void AC_PlayerCharacter::P_OnBattleTypeChanged(EBattleState InPrevType, EBattleState InNewType)
{
}



