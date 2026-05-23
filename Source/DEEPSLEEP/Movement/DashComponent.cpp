#include "DashComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UDashComponent::UDashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDashComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsDashing)
	{
		return;
	}

	const UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	if (World->GetTimeSeconds() >= DashEndTime)
	{
		EndDash();
	}
}

bool UDashComponent::TryDash(const FVector& WorldDirection)
{
	if (!CanDash())
	{
		return false;
	}

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return false;
	}

	UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement();
	if (!MoveComp)
	{
		return false;
	}

	const FVector DashDirection = ResolveDashDirection(WorldDirection);
	if (DashDirection.IsNearlyZero())
	{
		return false;
	}

	CachedGroundFriction = MoveComp->GroundFriction;
	CachedBrakingFrictionFactor = MoveComp->BrakingFrictionFactor;

	MoveComp->GroundFriction = GroundFrictionWhileDashing;
	MoveComp->BrakingFrictionFactor = BrakingFrictionFactorWhileDashing;

	FVector NewVelocity = DashDirection * DashSpeed;
	if (bPreserveVerticalVelocity)
	{
		NewVelocity.Z = MoveComp->Velocity.Z;
	}

	MoveComp->Velocity = NewVelocity;
	bIsDashing = true;

	if (const UWorld* World = GetWorld())
	{
		const float CurrentTime = World->GetTimeSeconds();
		DashEndTime = CurrentTime + DashDuration;
		NextDashAllowedTime = CurrentTime + DashCooldown;
	}

	return true;
}

bool UDashComponent::IsOnCooldown() const
{
	const UWorld* World = GetWorld();
	if (!World)
	{
		return true;
	}

	return World->GetTimeSeconds() < NextDashAllowedTime;
}

void UDashComponent::EndDash()
{
	if (!bIsDashing)
	{
		return;
	}

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	UCharacterMovementComponent* MoveComp = OwnerCharacter ? OwnerCharacter->GetCharacterMovement() : nullptr;
	if (MoveComp)
	{
		MoveComp->GroundFriction = CachedGroundFriction;
		MoveComp->BrakingFrictionFactor = CachedBrakingFrictionFactor;
	}

	bIsDashing = false;
}

bool UDashComponent::CanDash() const
{
	const UWorld* World = GetWorld();
	const ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	const UCharacterMovementComponent* MoveComp = OwnerCharacter ? OwnerCharacter->GetCharacterMovement() : nullptr;

	if (!World || !MoveComp || bIsDashing)
	{
		return false;
	}

	if (World->GetTimeSeconds() < NextDashAllowedTime)
	{
		return false;
	}

	if (!bCanDashInAir && MoveComp->IsFalling())
	{
		return false;
	}

	return true;
}

FVector UDashComponent::ResolveDashDirection(const FVector& WorldDirection) const
{
	const ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return FVector::ZeroVector;
	}

	FVector DashDirection = WorldDirection;
	if (DashDirection.IsNearlyZero())
	{
		DashDirection = OwnerCharacter->GetActorForwardVector();
	}

	DashDirection.Z = 0.0f;
	return DashDirection.GetSafeNormal();
}
