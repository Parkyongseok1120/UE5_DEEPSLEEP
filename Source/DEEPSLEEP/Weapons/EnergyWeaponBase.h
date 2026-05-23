// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyWeaponBase.generated.h"

/**
 * 에너지 무기 종류 - 프래그마타 스타일 에너지 무기
 */
UENUM(BlueprintType)
enum class EEnergyWeaponType : uint8
{
	None            UMETA(DisplayName = "None"),
	PlasmaGun       UMETA(DisplayName = "Plasma Gun"),      // 빠른 연사, 낮은 피해
	LightningBolt   UMETA(DisplayName = "Lightning Bolt"),  // 중거리 광역 공격
	EnergyBlade     UMETA(DisplayName = "Energy Blade"),    // 근접 고피해
	EMPDisruptor    UMETA(DisplayName = "EMP Disruptor")    // 기절 및 범위 제어
};

/**
 * 에너지 무기 피해 유형
 */
UENUM(BlueprintType)
enum class EEnergyDamageType : uint8
{
	Thermal     UMETA(DisplayName = "Thermal"),
	Electric    UMETA(DisplayName = "Electric"),
	Plasma      UMETA(DisplayName = "Plasma"),
	Cryo        UMETA(DisplayName = "Cryogenic")
};

/**
 * 시스템 내 모든 에너지 무기의 기본 클래스
 * 에너지 관리, 발사 메커니즘, 무기 전환 기능을 제공합니다.
 */
UCLASS(abstract)
class DEEPSLEEP_API AEnergyWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AEnergyWeaponBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	/** 무기 발사를 시도합니다. */
	virtual bool TryFire(AActor* FiringActor);

	/** 에너지를 재장전합니다(해당하는 경우). */
	virtual void ReloadEnergy();

	/** 무기 유형을 반환합니다. */
	FORCEINLINE EEnergyWeaponType GetWeaponType() const { return WeaponType; }

	/** 현재 에너지량을 반환합니다. */
	FORCEINLINE float GetCurrentEnergy() const { return CurrentEnergy; }

	/** 최대 에너지 용량을 반환합니다. */
	FORCEINLINE float GetMaxEnergy() const { return MaxEnergy; }

	/** 무기가 발사 가능한지 확인합니다. */
	bool CanFire() const;

protected:
	/** 실제 발사 동작을 블루프린트 또는 파생 클래스에서 수행합니다. */
	UFUNCTION(BlueprintNativeEvent, Category="Weapon")
	bool PerformFire(AActor* FiringActor);

	/** 발사용 에너지를 소모합니다. */
	void ConsumeEnergy(float Amount);

	/** 시간에 따라 에너지를 회복합니다. */
	void RegenerateEnergy(float DeltaTime);

private:
	// === 무기 식별 ===

	/** 이 무기의 유형 */
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	EEnergyWeaponType WeaponType = EEnergyWeaponType::None;

	/** 이 무기가 주는 피해 유형 */
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	EEnergyDamageType DamageType = EEnergyDamageType::Thermal;

	// === 에너지 시스템 ===

	/** 최대 에너지 용량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Energy", meta=(AllowPrivateAccess="true", ClampMin=10))
	float MaxEnergy = 100.0f;

	/** 현재 에너지량 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon|Energy", meta=(AllowPrivateAccess="true"))
	float CurrentEnergy = 100.0f;

	/** 한 번의 사격/공격당 에너지 소모량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Energy", meta=(AllowPrivateAccess="true", ClampMin=1))
	float EnergyCostPerShot = 10.0f;

	/** 초당 수동 에너지 회복량(외부에서 관리하면 0으로 설정) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Energy", meta=(AllowPrivateAccess="true", ClampMin=0))
	float EnergyRegenRate = 5.0f;

	// === 연사 속도 시스템 ===

	/** 발사 간 최소 시간(초) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|FireRate", meta=(AllowPrivateAccess="true", ClampMin=0.1))
	float FireCooldown = 0.2f;

	/** 다음 발사가 가능한 시점 */
	float NextFireTime = 0.0f;

	// === 피해 시스템 ===

	/** 이 무기의 기본 피해량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Damage", meta=(AllowPrivateAccess="true", ClampMin=1))
	float BaseDamage = 25.0f;
};
