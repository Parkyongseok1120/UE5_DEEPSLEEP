// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManagerComponent.generated.h"

class AEnergyWeaponBase;

/**
 * 무기 관리 컴포넌트 - 플레이어의 여러 에너지 무기를 관리합니다.
 * 무기 전환과 장착을 처리하고 현재 활성 무기에 접근할 수 있게 합니다.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEEPSLEEP_API UWeaponManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponManagerComponent();

	// ~UActorComponent 인터페이스 시작
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// ~UActorComponent 인터페이스 종료

public:
	/** 지정한 인덱스의 무기로 전환합니다. */
	void SwitchToWeapon(int32 WeaponIndex);

	/** 다음 무기로 전환합니다. */
	void SwitchToNextWeapon();

	/** 이전 무기로 전환합니다. */
	void SwitchToPreviousWeapon();

	/** 새 무기를 장착합니다(인벤토리에 추가). */
	bool EquipWeapon(AEnergyWeaponBase* Weapon);

	/** 지정한 인덱스의 무기를 해제합니다. */
	void UnequipWeapon(int32 WeaponIndex);

	/** 현재 장착된 무기를 반환합니다. */
	FORCEINLINE AEnergyWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

	/** 현재 무기 인덱스를 반환합니다. */
	FORCEINLINE int32 GetCurrentWeaponIndex() const { return CurrentWeaponIndex; }

	/** 장착한 무기의 총 개수를 반환합니다. */
	FORCEINLINE int32 GetEquippedWeaponCount() const { return EquippedWeapons.Num(); }

	/** 현재 장착된 무기가 있는지 확인합니다. */
	FORCEINLINE bool HasEquippedWeapon() const { return CurrentWeapon != nullptr; }

protected:
	/** 무기 전환을 검증하고 적용합니다. */
	void ApplyWeaponSwitch(int32 NewIndex);

	/** 무기 전환 이벤트를 블루프린트에 알립니다. */
	UFUNCTION(BlueprintImplementableEvent, Category="Weapon")
	void OnWeaponSwitched(AEnergyWeaponBase* OldWeapon, AEnergyWeaponBase* NewWeapon);

private:
	// === 무기 인벤토리 ===

	/** 장착한 모든 무기 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="WeaponManager", meta=(AllowPrivateAccess="true"))
	TArray<TObjectPtr<AEnergyWeaponBase>> EquippedWeapons;

	/** 현재 활성 무기 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="WeaponManager", meta=(AllowPrivateAccess="true"))
	TObjectPtr<AEnergyWeaponBase> CurrentWeapon;

	/** 인벤토리에서 현재 활성 무기의 인덱스 */
	int32 CurrentWeaponIndex = INDEX_NONE;
};
