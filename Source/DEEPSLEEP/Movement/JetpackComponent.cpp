// 에픽게임즈의 모든 권리 보유.

#include "JetpackComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UJetpackComponent::UJetpackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UJetpackComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 연료를 최대치로 초기화
	CurrentFuel = MaxFuel;
}

void UJetpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const bool bWantsThrust = bIsThrustingForward || bIsThrustingUp;

	if (bWantsThrust && CanApplyThrust())
	{
		// 추력 사용 중 연료 소모
		CurrentFuel = FMath::Max(0.0f, CurrentFuel - FuelConsumptionRate * DeltaTime);

		// 추력이 활성화되어 있고 연료가 있으면 추력을 적용
		if (HasFuel())
		{
			ApplyThrust(DeltaTime);
		}
	}
	else if (!bIsDodging)
	{
		// 지상에 있거나 제트팩을 적극적으로 사용하지 않을 때 연료 회복
		RegenerateFuel(DeltaTime);
	}
}

void UJetpackComponent::ActivateThrust(bool bForward, bool bUp)
{
	bIsThrustingForward = bForward;
	bIsThrustingUp = bUp;
}

void UJetpackComponent::PerformBurstDodge(const FVector& Direction)
{
	// 회피에 필요한 연료가 충분한지 확인
	if (CurrentFuel < BurstDodgeFuelCost || bIsDodging)
	{
		return;
	}

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	UCharacterMovementComponent* CharacterMovement = OwnerCharacter ? OwnerCharacter->GetCharacterMovement() : nullptr;
	UWorld* World = GetWorld();
	if (!CharacterMovement || Direction.IsNearlyZero() || !World)
	{
		return;
	}

	// 회피용 연료 소모
	CurrentFuel -= BurstDodgeFuelCost;

	bIsDodging = true;

	// 버스트 회피 속도 적용
	FVector DodgeVelocity = Direction.GetSafeNormal() * BurstDodgeSpeed;
	CharacterMovement->Velocity = DodgeVelocity;

	// 회피 종료 타이머 설정
	World->GetTimerManager().SetTimer(DodgeTimerHandle, FTimerDelegate::CreateLambda([this]()
	{
		bIsDodging = false;
	}), BurstDodgeDuration, false);
}

void UJetpackComponent::RegenerateFuel(float DeltaTime)
{
	CurrentFuel = FMath::Min(MaxFuel, CurrentFuel + FuelRegenRate * DeltaTime);
}

bool UJetpackComponent::CanApplyThrust() const
{
	const ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	const UCharacterMovementComponent* CharacterMovement = OwnerCharacter ? OwnerCharacter->GetCharacterMovement() : nullptr;
	return CharacterMovement != nullptr && CharacterMovement->IsFalling() && !bIsDodging;
}

void UJetpackComponent::ApplyThrust(float DeltaTime)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	UCharacterMovementComponent* CharacterMovement = OwnerCharacter ? OwnerCharacter->GetCharacterMovement() : nullptr;
	if (!CharacterMovement)
	{
		return;
	}

	// 추력 방향 계산을 위한 카메라 회전값 가져오기
	FRotator CameraRotation = OwnerCharacter->GetControlRotation();
	FVector ForwardDir = FRotationMatrix(CameraRotation).GetUnitAxis(EAxis::X).GetSafeNormal2D();

	// 전방 추력이 활성화되어 있으면 적용
	if (bIsThrustingForward && HasFuel())
	{
		CharacterMovement->Velocity += ForwardDir * ForwardThrustPower * DeltaTime;
	}

	// 상승 추력이 활성화되어 있으면 적용
	if (bIsThrustingUp && HasFuel())
	{
		CharacterMovement->Velocity.Z += UpwardThrustPower * DeltaTime;
	}
}
