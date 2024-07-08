// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Deepsleep_LegacyCharacter.h"
#include "Projectile/ProjectileBase.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

// Sets default values
ADeepsleep_LegacyCharacter::ADeepsleep_LegacyCharacter():MuzzleSocketName(FName(TEXT("Muzzle")))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	AmmoCount = 0;
	bCanReload = false;
	RemainAmmoCount = 30;
	bisStopShooting = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	
}


// Called when the game starts or when spawned
void ADeepsleep_LegacyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	
}

void ADeepsleep_LegacyCharacter::PlayFireEffects()
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, FP_Gun, MuzzleSocketName);
	}

	//CameraShake
	APlayerController* PC = Cast<APlayerController>(this->GetController());
	
	if (PC)
	{
		PC->ClientStartCameraShake((FireCamShake));
	}
}

void ADeepsleep_LegacyCharacter::Reload()
{
	if(bCanReload != false)
	{
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadingSound, GetActorLocation());
		}
		bisStopShooting = true;
		FTimerHandle ReloadingTimerHandle;
		float ReloadingTime =3.f;

		GetWorld()->GetTimerManager().SetTimer(ReloadingTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			AmmoCount = 0;
			RemainAmmoCount = 30;
			bisStopShooting = false;
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(ReloadingTimerHandle);
		}), ReloadingTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
	}
	bCanReload = false;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADeepsleep_LegacyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADeepsleep_LegacyCharacter::OnFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ADeepsleep_LegacyCharacter::Reload);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADeepsleep_LegacyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADeepsleep_LegacyCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADeepsleep_LegacyCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADeepsleep_LegacyCharacter::LookUpAtRate);
}

void ADeepsleep_LegacyCharacter::OnFire()
{
	if(AmmoCount < 30 && RemainAmmoCount > 0 && bisStopShooting == false)
	{
		// try and fire a projectile
		if (ProjectileClass != nullptr)
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				
					const FRotator SpawnRotation = GetControlRotation();
					// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
					const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

					//Set Spawn Collision Handling Override
					FActorSpawnParameters ActorSpawnParams;
					ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

					// spawn the projectile at the muzzle
					PlayerProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					if(PlayerProjectile)
					{
						PlayerProjectile->SetOwner(this);
					}
					PlayFireEffects();
				
			}
		}

		// try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		// try and play a firing animation if specified
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
		AmmoCount++;
		RemainAmmoCount = 30 - AmmoCount;
		if(AmmoCount >= 1)
		{
			bCanReload = true;
		}
	}
	else
	{
		Reload();
	}
		
}

void ADeepsleep_LegacyCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADeepsleep_LegacyCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADeepsleep_LegacyCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADeepsleep_LegacyCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
