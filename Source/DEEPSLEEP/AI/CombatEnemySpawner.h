// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatActivatable.h"
#include "CombatEnemySpawner.generated.h"

class UCapsuleComponent;
class UArrowComponent;
class ACombatEnemy;

/**
 *  적 캐릭터를 생성하고 그들의 사망을 감시하는 기본 액터입니다.
 *  적은 하나씩 생성되며, 스포너는 현재 적이 죽을 때까지 기다렸다가 새 적을 생성합니다.
 *  스포너는 전투 활성화 가능 인터페이스를 통해 원격으로 활성화될 수 있습니다.
 *  마지막 적이 죽으면 스포너는 다른 전투 활성화 가능 액터도 활성화할 수 있습니다.
 */
UCLASS(abstract)
class ACombatEnemySpawner : public AActor, public ICombatActivatable
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* SpawnCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* SpawnDirection;

protected:

	/** Type of 적 to s폰 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner")
	TSubclassOf<ACombatEnemy> EnemyClass;

	/** If true, first 적 will be s폰ed as soon as game 시작s */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner")
	bool bShouldSpawnEnemiesImmediately = true;

	/** Time to wait before s폰ing first 적 on game 시작 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (ClampMin = 0, ClampMax = 10))
	float InitialSpawnDelay = 5.0f;

	/** Number of enemies to s폰 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (ClampMin = 0, ClampMax = 100))
	int32 SpawnCount = 1;

	/** Time to wait before s폰ing next 적 after current one dies */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Spawner", meta = (ClampMin = 0, ClampMax = 10))
	float RespawnDelay = 5.0f;

	/** Time to wait after this s폰er is depleted before activating 액터 list */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Activation", meta = (ClampMin = 0, ClampMax = 10))
	float ActivationDelay = 1.0f;

	/** List of 액터s to activate after last 적 dies */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Activation")
	TArray<AActor*> ActorsToActivateWhenDepleted;

	/** Flag to this is only activated once */
	bool bHasBeenActivated = false;

	/** Timer to s폰 enemies after a delay */
	FTimerHandle SpawnTimer;

public:	
	
	/** 생성자 */
	ACombatEnemySpawner();

public:

	/** 초기화 */
	virtual void BeginPlay() override;

	/** 정리 작업 */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

protected:

	/** S폰 an 적 and subscribe to its death event */
	void SpawnEnemy();

	/** Called 때 s폰ed 적 has died */
	UFUNCTION()
	void OnEnemyDied();

	/** Called after last s폰ed 적 has died */
	void SpawnerDepleted();

public:

	// ~ICombatActivatable 인터페이스 시작

	/** S폰er를 토글합니다. */
	UFUNCTION(BlueprintCallable, Category="Activatable")
	virtual void ToggleInteraction(AActor* ActivationInstigator) override;

	/** Activates S폰er */
	UFUNCTION(BlueprintCallable, Category="Activatable")
	virtual void ActivateInteraction(AActor* ActivationInstigator) override;

	/** S폰er를 비활성화합니다. */
	UFUNCTION(BlueprintCallable, Category="Activatable")
	virtual void DeactivateInteraction(AActor* ActivationInstigator) override;

	// ~IActivatable 인터페이스 종료
};
