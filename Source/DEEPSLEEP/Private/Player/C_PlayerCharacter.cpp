// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ActorComponent/C_PlayerMovementComponent.h"
#include "Util/Global.h"

AC_PlayerCharacter::AC_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//CreateComponent : Use to CHelpers.hpp
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent<UCameraComponent>(this, &PlayerCamera, "Camera", SpringArm);
	CHelpers::CreateActorComponent<UC_PlayerMovementComponent>(this, &Movement, "Movement");

	
	GetMesh()->SetRelativeLocation(FVector(0,0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	SpringArm->SetRelativeRotation(FRotator(-10 ,90,0));
	SpringArm->SetRelativeLocation(FVector(-19,0,+130));

	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

	SpringArm->TargetArmLength = 200;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	bIsPlayerSprinting = Movement->GetbIsSprinting();
	
	
}

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
	bWantsToZoom = true;
	
	if( bIsPlayerSprinting == true )
    {
    bIsPlayerSprinting = false;
   // GetCharacterMovement()->MaxWalkSpeed = SetSpeed();
    }

}

void AC_PlayerCharacter::EndZoom()
{
	bWantsToZoom = false;
	SpringArm->bEnableCameraLag = true;
}

// Called when the game starts or when spawned
void AC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultFOV = PlayerCamera->FieldOfView;
	
	Movement->EndSprint();
	Movement->DisableControlRotation();
	
}

// Called to bind functionality to input
void AC_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//--------------------------------KeyBoard----------------------------------------
	
	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("MoveForward", Movement, &UC_PlayerMovementComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", Movement, &UC_PlayerMovementComponent::OnMoveRight);
	PlayerInputComponent->BindAxis("VerticalLook", Movement, &UC_PlayerMovementComponent::OnVerticalLook);
	PlayerInputComponent->BindAxis("HorizontalLook", Movement, &UC_PlayerMovementComponent::OnHorizontalLook);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, Movement, &UC_PlayerMovementComponent::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, Movement, &UC_PlayerMovementComponent::EndSprint);

	PlayerInputComponent->BindAction("CameraZoom", IE_Pressed, this, &AC_PlayerCharacter::BeginZoom);
	PlayerInputComponent->BindAction("CameraZoom", IE_Released, this, &AC_PlayerCharacter::EndZoom);

	//--------------------------------KeyBoard----------------------------------------
}

// Called every frame
void AC_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 i = 0;
	float CurrentSpeed = this->Movement->GetPlayerSpeed();
	CLog::Log(CurrentSpeed);

	//'ZoomedFOV' if zoom promotion is required, otherwise 'DefaultFOV' is retained.
	float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;

	//CurrentFOV : Current field of view
	float NewFOV = FMath::FInterpTo(PlayerCamera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);

	PlayerCamera->SetFieldOfView(NewFOV);
	
	if(bWantsToZoom == true)
	{
		//this->SetActorRelativeRotation(FRotator(DefaultFOV));
	}

}

