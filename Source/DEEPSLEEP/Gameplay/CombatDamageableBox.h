// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatDamageable.h"
#include "CombatDamageableBox.generated.h"

/**
 *  전투 피해 가능 인터페이스를 통해 피해에 반응하는 단순 물리 박스입니다.
 */
UCLASS(abstract)
class ACombatDamageableBox : public AActor, public ICombatDamageable
{
	GENERATED_BODY()
	
	/** 피해able box mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

public:	

	/** 생성자 */
	ACombatDamageableBox();

protected:

	/** Amount of HP this box 시작s with. */
	UPROPERTY(EditAnywhere, Category="Damage")
	float CurrentHP = 3.0f;

	/** Time to wait before we remove this box from level. */
	UPROPERTY(EditAnywhere, Category="Damage", meta = (ClampMin = 0, ClampMax = 10, Units = "s"))
	float DeathDelayTime = 6.0f;

	/** Timer to defer destruction of this box after its HP are depleted */
	FTimerHandle DeathTimer;

	/** 블루프린트 피해 handler for effect playback */
	UFUNCTION(BlueprintImplementableEvent, Category="Damage")
	void OnBoxDamaged(const FVector& DamageLocation, const FVector& DamageImpulse);

	/** 블루프린트 destruction handler for effect playback */
	UFUNCTION(BlueprintImplementableEvent, Category="Damage")
	void OnBoxDestroyed();

	/** Timer callback to remove box from level after it dies */
	void RemoveFromLevel();

public:

	/** 종료 시 정리 작업 */
	void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	// ~Begin Combat피해able interface

	/** 피해 and knockback events를 처리합니다. */
	virtual void ApplyDamage(float Damage, AActor* DamageCauser, const FVector& DamageLocation, const FVector& DamageImpulse) override;

	/** death events를 처리합니다. */
	virtual void HandleDeath() override;

	/** healing events를 처리합니다. */
	virtual void ApplyHealing(float Healing, AActor* Healer) override;

	/** 들어오는 공격에 반응할 수 있게 합니다. */
	virtual void NotifyDanger(const FVector& DangerLocation, AActor* DangerSource) override;

	// ~End Combat피해able interface
};
