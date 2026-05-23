// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatAttacker.h"
#include "CombatDamageable.h"
#include "Animation/AnimMontage.h"
#include "Engine/TimerHandle.h"
#include "CombatEnemy.generated.h"

class UWidgetComponent;
class UCombatLifeBar;
class UAnimMontage;

/** 상태 트리용 공격 애니메이션 완료 델리게이트 */
DECLARE_DELEGATE(FOnEnemyAttackCompleted);

/** 상태 트리용 착지 델리게이트 */
DECLARE_DELEGATE(FOnEnemyLanded);

/** 적 사망 델리게이트 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDied);

/**
 *  전투 능력을 가진 인공지능 제어 캐릭터입니다.
 *  내장된 인공지능 컨트롤러가 상태 트리를 통해 로직을 수행합니다.
 */
UCLASS(abstract)
class ACombatEnemy : public ACharacter, public ICombatAttacker, public ICombatDamageable
{
	GENERATED_BODY()

	/** Life bar 위젯 컴포넌트 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* LifeBar;

public:
	
	/** 생성자 */
	ACombatEnemy();

protected:

	/** Max amount of HP 캐릭터 will have on res폰 */
	UPROPERTY(EditAnywhere, Category="Damage")
	float MaxHP = 3.0f;

public:

	/** Current amount of HP 캐릭터 has */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Damage", meta = (ClampMin = 0, ClampMax = 100))
	float CurrentHP = 0.0f;

protected:

	/** Name of pelvis bone, for 피해 래그돌 physics */
	UPROPERTY(EditAnywhere, Category="Damage")
	FName PelvisBoneName;

	/** Pointer to 라이프 바 위젯 */
	UPROPERTY(EditAnywhere, Category="Damage")
	UCombatLifeBar* LifeBarWidget;

	/** If true, 캐릭터 is currently playing an attack animation */
	bool bIsAttacking = false;

	/** Distance ahead of 캐릭터 that 근접 attack sphere collision 추적s will extend */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Trace", meta = (ClampMin = 0, ClampMax = 500, Units = "cm"))
	float MeleeTraceDistance = 75.0f;

	/** Radius of sphere 추적 for 근접 attacks */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Trace", meta = (ClampMin = 0, ClampMax = 500, Units = "cm"))
	float MeleeTraceRadius = 50.0f;

	/** Amount of 피해 a 근접 attack will deal */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Damage", meta = (ClampMin = 0, ClampMax = 100))
	float MeleeDamage = 1.0f;

	/** Amount of knockback impulse a 근접 attack will apply */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Damage", meta = (ClampMin = 0, ClampMax = 1000, Units = "cm/s"))
	float MeleeKnockbackImpulse = 150.0f;

	/** Amount of upwards impulse a 근접 attack will apply */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Damage", meta = (ClampMin = 0, ClampMax = 1000, Units = "cm/s"))
	float MeleeLaunchImpulse = 350.0f;

	/** 애님 몽타주 that will play for 콤보 attacks */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Combo")
	UAnimMontage* ComboAttackMontage;

	/** Names of 애님 몽타주 sections that correspond to each stage of 콤보 attack */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Combo")
	TArray<FName> ComboSectionNames;

	/** Target number of attacks in 콤보 attack 연계 we're playing */
	int32 TargetComboCount = 0;

	/** Index of current stage of 근접 attack 콤보 */
	int32 CurrentComboAttack = 0;

	/** 애님 몽타주 that will play for 차지 attacks */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Charged")
	UAnimMontage* ChargedAttackMontage;

	/** Name of 애님 몽타주 section that corresponds to charge 반복 */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Charged")
	FName ChargeLoopSection;

	/** Name of 애님 몽타주 section that corresponds to attack */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Charged")
	FName ChargeAttackSection;

	/** Minimum number of charge animation 반복s that will be played by 인공지능 */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Charged", meta = (ClampMin = 1, ClampMax = 20))
	int32 MinChargeLoops = 2;

	/** Maximum number of charge animation 반복s that will be played by 인공지능 */
	UPROPERTY(EditAnywhere, Category="Melee Attack|Charged", meta = (ClampMin = 1, ClampMax = 20))
	int32 MaxChargeLoops = 5;

	/** Target number of charge animation 반복s to play in this 차지 attack */
	int32 TargetChargeLoops = 0;

	/** Number of charge animation 반복 currently playing */
	int32 CurrentChargeLoop = 0;

	/** Time to wait before removing this 캐릭터 from level after it dies */
	UPROPERTY(EditAnywhere, Category="Death")
	float DeathRemovalTime = 5.0f;

	/** Enemy death 타이머 */
	FTimerHandle DeathTimer;

	/** Attack montage 종료 delegate */
	FOnMontageEnded OnAttackMontageEnded;

	/** Last recorded location we're being attacked from */
	FVector LastDangerLocation = FVector::ZeroVector;

	/** Last recorded game time we were attacked */
	float LastDangerTime = -1000.0f;

public:
	/** Attack completed internal delegate to 노티파이 상태 트리 tasks */
	FOnEnemyAttackCompleted OnAttackCompleted;

	/** 착지 internal delegate to 노티파이 상태 트리 tasks. We use this instead of built-in 착지 delegate so we can bind to a Lambda in 상태 트리 tasks */
	FOnEnemyLanded OnEnemyLanded;

	/** Enemy died delegate. Allows external subscribers to respond to 적 death */
	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnEnemyDied OnEnemyDied;

public:

	/** an 인공지능-initiated 콤보 attack. Number of hits will be decided by this 캐릭터를 수행합니다. */
	void DoAIComboAttack();

	/** an 인공지능-initiated 차지 attack. Charge time will be decided by this 캐릭터를 수행합니다. */
	void DoAIChargedAttack();

	/** Called from a delegate 때 attack montage ends */
	void AttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	/** last recorded location we were attacked from를 반환합니다. */
	const FVector& GetLastDangerLocation() const;

	/** last game time we were attacked를 반환합니다. */
	float GetLastDangerTime() const;

public:

	// ~ICombatAttacker 인터페이스 시작

	/** an attack's collision 검사를 수행합니다. */
	virtual void DoAttackTrace(FName DamageSourceBone) override;

	/** a 콤보 attack's 검사 to 계속 연계를 수행합니다. */
	UFUNCTION(BlueprintCallable, Category="Attacker")
	virtual void CheckCombo() override;

	/** a 차지 attack's 검사 to 반복 charge animation를 수행합니다. */
	UFUNCTION(BlueprintCallable, Category="Attacker")
	virtual void CheckChargedAttack() override;

	// ~ICombatAttacker 인터페이스 종료

	// ~ICombat피해able 인터페이스 시작

	/** 피해 and knockback events를 처리합니다. */
	virtual void ApplyDamage(float Damage, AActor* DamageCauser, const FVector& DamageLocation, const FVector& DamageImpulse) override;

	/** death events를 처리합니다. */
	virtual void HandleDeath() override;

	/** healing events를 처리합니다. */
	virtual void ApplyHealing(float Healing, AActor* Healer) override;

	/** Allows 적 to react to incoming attacks */
	virtual void NotifyDanger(const FVector& DangerLocation, AActor* DangerSource) override;

	// ~ICombat피해able 인터페이스 종료

protected:

	/** Removes this 캐릭터 from level after it dies */
	void RemoveFromLevel();

public:

	/** Overrides default 피해 처리 functionality */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/** Overrides landing to reset 피해 래그돌 physics */
	virtual void Landed(const FHitResult& Hit) override;

protected:

	/** 블루프린트 handler to play 피해 received effects */
	UFUNCTION(BlueprintImplementableEvent, Category="Combat")
	void ReceivedDamage(float Damage, const FVector& ImpactPoint, const FVector& DamageDirection);

protected:

	/** 게임플레이 초기화 */
	virtual void BeginPlay() override;

	/** 종료 시 정리 작업 */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
};
