// 에픽게임즈의 모든 권리 보유.

#include "WeaponManagerComponent.h"
#include "Weapons/EnergyWeaponBase.h"

UWeaponManagerComponent::UWeaponManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // 무기 전환은 지속적인 틱이 필요하지 않습니다.
}

void UWeaponManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// 첫 번째 무기가 있으면 자동으로 장착
	if (EquippedWeapons.Num() > 0 && CurrentWeapon == nullptr)
	{
		ApplyWeaponSwitch(0);
	}
}

void UWeaponManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// 현재는 프레임별 로직이 필요하지 않음
}

void UWeaponManagerComponent::SwitchToWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= EquippedWeapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index: %d"), WeaponIndex);
		return;
	}
	
	ApplyWeaponSwitch(WeaponIndex);
}

void UWeaponManagerComponent::SwitchToNextWeapon()
{
	if (EquippedWeapons.Num() <= 1)
	{
		return; // 전환할 다른 무기가 없습니다.
	}
	
	int32 NextIndex = (CurrentWeaponIndex + 1) % EquippedWeapons.Num();
	ApplyWeaponSwitch(NextIndex);
}

void UWeaponManagerComponent::SwitchToPreviousWeapon()
{
	if (EquippedWeapons.Num() <= 1)
	{
		return; // 전환할 다른 무기가 없습니다.
	}
	
	int32 PrevIndex = (CurrentWeaponIndex - 1 + EquippedWeapons.Num()) % EquippedWeapons.Num();
	ApplyWeaponSwitch(PrevIndex);
}

bool UWeaponManagerComponent::EquipWeapon(AEnergyWeaponBase* Weapon)
{
	if (!Weapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot equip null weapon"));
		return false;
	}
	
	// 이미 장착되어 있는지 확인
	for (int32 i = 0; i < EquippedWeapons.Num(); ++i)
	{
		if (EquippedWeapons[i] == Weapon)
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon already equipped"));
			return false;
		}
	}
	
	// 인벤토리에 추가
	EquippedWeapons.Add(Weapon);
	
	// 첫 번째 무기라면 자동으로 장착
	if (CurrentWeapon == nullptr)
	{
		ApplyWeaponSwitch(EquippedWeapons.Num() - 1);
	}
	
	return true;
}

void UWeaponManagerComponent::UnequipWeapon(int32 WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= EquippedWeapons.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index for unequipping: %d"), WeaponIndex);
		return;
	}
	
	AEnergyWeaponBase* OldWeapon = CurrentWeapon;
	const bool bRemovedCurrentWeapon = (WeaponIndex == CurrentWeaponIndex);
	
	// 배열에서 제거
	EquippedWeapons.RemoveAt(WeaponIndex);

	if (EquippedWeapons.Num() == 0)
	{
		CurrentWeapon = nullptr;
		CurrentWeaponIndex = INDEX_NONE;
	}
	else if (bRemovedCurrentWeapon)
	{
		CurrentWeaponIndex = FMath::Min(WeaponIndex, EquippedWeapons.Num() - 1);
		CurrentWeapon = EquippedWeapons[CurrentWeaponIndex];
	}
	else
	{
		if (WeaponIndex < CurrentWeaponIndex)
		{
			--CurrentWeaponIndex;
		}

		CurrentWeapon = EquippedWeapons[CurrentWeaponIndex];
	}
	
	// 무기 전환을 블루프린트에 알림
	if (OldWeapon != CurrentWeapon)
	{
		OnWeaponSwitched(OldWeapon, CurrentWeapon);
	}
}

void UWeaponManagerComponent::ApplyWeaponSwitch(int32 NewIndex)
{
	if (!EquippedWeapons.IsValidIndex(NewIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid weapon index: %d"), NewIndex);
		return;
	}

	AEnergyWeaponBase* NewWeapon = EquippedWeapons[NewIndex];
	if (NewIndex == CurrentWeaponIndex && CurrentWeapon == NewWeapon)
	{
		return; // 이미 이 무기를 사용 중입니다.
	}
	
	AEnergyWeaponBase* OldWeapon = CurrentWeapon;
	CurrentWeaponIndex = NewIndex;
	CurrentWeapon = NewWeapon;
	
	// 무기 전환을 블루프린트에 알림(애니메이션, 사운드, UI 갱신용)
	OnWeaponSwitched(OldWeapon, CurrentWeapon);
}
