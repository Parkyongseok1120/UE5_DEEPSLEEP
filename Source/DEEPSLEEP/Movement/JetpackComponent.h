// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JetpackComponent.generated.h"

/**
 * 제트팩 이동 컴포넌트 - 프래그마타 스타일 제트팩 시스템
 * 추력 기반 공중 이동과 버스트 회피 기능을 제공합니다.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEEPSLEEP_API UJetpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UJetpackComponent();

	// ~UActorComponent 인터페이스 시작
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	// ~UActorComponent 인터페이스 종료

public:
	/** 지정한 방향으로 제트팩 추력을 활성화합니다. */
	void ActivateThrust(bool bForward, bool bUp);

	/** 버스트 회피를 수행합니다(짧은 무적 판정이 있는 대시). */
	void PerformBurstDodge(const FVector& Direction);

	/** 연료가 남아 있는지 확인합니다. */
	FORCEINLINE bool HasFuel() const { return CurrentFuel > 0.0f; }

	/** 현재 연료 비율(0.0 - 1.0)을 반환합니다. */
	FORCEINLINE float GetFuelPercentage() const { return MaxFuel > 0.0f ? CurrentFuel / MaxFuel : 0.0f; }

	/** 현재 회피 중인지 확인합니다. */
	FORCEINLINE bool IsDodging() const { return bIsDodging; }

	/** 전방 추력이 현재 활성화되어 있는지 확인합니다. */
	FORCEINLINE bool IsThrustingForward() const { return bIsThrustingForward; }

	/** 상승 추력이 현재 활성화되어 있는지 확인합니다. */
	FORCEINLINE bool IsThrustingUp() const { return bIsThrustingUp; }

protected:
	/** 시간에 따라 연료를 회복합니다. */
	void RegenerateFuel(float DeltaTime);

	/** 캐릭터에 추력 힘을 적용합니다. */
	void ApplyThrust(float DeltaTime);

	/** 소유자가 공중에 있어 추력을 받을 수 있으면 true를 반환합니다. */
	bool CanApplyThrust() const;

private:
	// === 연료 시스템 ===
	
	/** 최대 연료 용량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Fuel", meta=(AllowPrivateAccess="true"))
	float MaxFuel = 100.0f;

	/** 현재 연료량 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Jetpack|Fuel", meta=(AllowPrivateAccess="true"))
	float CurrentFuel = 100.0f;

	/** 초당 연료 회복량(지상에 있거나 추력을 사용하지 않을 때만) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Fuel", meta=(AllowPrivateAccess="true", ClampMin=0))
	float FuelRegenRate = 5.0f;

	/** 추력 사용 중 초당 연료 소모량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Fuel", meta=(AllowPrivateAccess="true", ClampMin=0))
	float FuelConsumptionRate = 15.0f;

	// === 추력 시스템 ===

	/** 전방 추력 세기 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Thrust", meta=(AllowPrivateAccess="true", ClampMin=0))
	float ForwardThrustPower = 600.0f;

	/** 상승 추력 세기 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Thrust", meta=(AllowPrivateAccess="true", ClampMin=0))
	float UpwardThrustPower = 800.0f;

	/** 추력 사용 중 공중 제어 배수 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Thrust", meta=(AllowPrivateAccess="true", ClampMin=0, ClampMax=1))
	float AirControlMultiplier = 0.8f;

	// === 버스트 회피 시스템 ===

	/** 버스트 회피 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Dodge", meta=(AllowPrivateAccess="true", ClampMin=0))
	float BurstDodgeSpeed = 2000.0f;

	/** 버스트 회피 지속 시간 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Dodge", meta=(AllowPrivateAccess="true", ClampMin=0, ClampMax=1, Units="s"))
	float BurstDodgeDuration = 0.2f;

	/** 버스트 회피 연료 소모량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jetpack|Dodge", meta=(AllowPrivateAccess="true", ClampMin=0))
	float BurstDodgeFuelCost = 20.0f;

	// === 상태 플래그 ===

	/** 현재 추력을 적용 중인지 여부 */
	bool bIsThrustingForward = false;
	bool bIsThrustingUp = false;

	/** 현재 버스트 회피 수행 중인지 여부 */
	bool bIsDodging = false;

	/** 회피 지속 시간 타이머 핸들 */
	FTimerHandle DodgeTimerHandle;
};
