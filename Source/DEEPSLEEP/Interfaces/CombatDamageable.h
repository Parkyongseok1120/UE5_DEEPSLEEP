// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatDamageable.generated.h"

/**
 *  전투 피해 가능 인터페이스
 *  functionality to handle 피해, healing, knockback and death를 제공합니다.
 *  Also provides functionality to warn 캐릭터s of incoming sources of 피해
 */
UINTERFACE(MinimalAPI, NotBlueprintable)
class UCombatDamageable : public UInterface
{
	GENERATED_BODY()
};

class ICombatDamageable
{
	GENERATED_BODY()

public:

	/** 피해 and knockback events를 처리합니다. */
	UFUNCTION(BlueprintCallable, Category="Damageable")
	virtual void ApplyDamage(float Damage, AActor* DamageCauser, const FVector& DamageLocation, const FVector& DamageImpulse) = 0;

	/** death events를 처리합니다. */
	UFUNCTION(BlueprintCallable, Category="Damageable")
	virtual void HandleDeath() = 0;

	/** healing events를 처리합니다. */
	UFUNCTION(BlueprintCallable, Category="Damageable")
	virtual void ApplyHealing(float Healing, AActor* Healer) = 0;

	/** Notifies 액터 of impending danger such as an incoming hit, allowing it to react. */
	UFUNCTION(BlueprintCallable, Category="Damageable")
	virtual void NotifyDanger(const FVector& DangerLocation, AActor* DangerSource) = 0;
};
