// 에픽게임즈의 모든 권리 보유.

#include "EnergyWeaponBase.h"

AEnergyWeaponBase::AEnergyWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false; // 현재 에너지 무기는 클라이언트 전용으로만 동작합니다.
}

void AEnergyWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 에너지를 최대치로 초기화
	CurrentEnergy = MaxEnergy;
}

void AEnergyWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 시간에 따라 수동으로 에너지를 회복
	RegenerateEnergy(DeltaTime);
}

bool AEnergyWeaponBase::TryFire(AActor* FiringActor)
{
	// 충분한 에너지가 있는지 확인
	if (!CanFire())
	{
		return false;
	}

	if (!PerformFire(FiringActor))
	{
		return false;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return false;
	}
	
	// 에너지 소모
	ConsumeEnergy(EnergyCostPerShot);
	
	// 발사 쿨다운 갱신
	NextFireTime = World->GetTimeSeconds() + FireCooldown;
	
	return true;
}

void AEnergyWeaponBase::ReloadEnergy()
{
	CurrentEnergy = MaxEnergy;
}

bool AEnergyWeaponBase::CanFire() const
{
	const UWorld* World = GetWorld();
	return World != nullptr && CurrentEnergy >= EnergyCostPerShot && 
	       World->GetTimeSeconds() >= NextFireTime;
}

bool AEnergyWeaponBase::PerformFire_Implementation(AActor* FiringActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Energy weapon %s has no fire implementation for %s"), *GetName(), *GetNameSafe(FiringActor));
	return false;
}

void AEnergyWeaponBase::ConsumeEnergy(float Amount)
{
	CurrentEnergy = FMath::Max(0.0f, CurrentEnergy - Amount);
}

void AEnergyWeaponBase::RegenerateEnergy(float DeltaTime)
{
	CurrentEnergy = FMath::Min(MaxEnergy, CurrentEnergy + EnergyRegenRate * DeltaTime);
}
