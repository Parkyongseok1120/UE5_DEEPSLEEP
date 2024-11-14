// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int32 CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;

public:
	void TakeDamage(float DamageAmount);
	void Heal(int32 HealAmount);
	
	// 생사 여부 확인
	bool IsAlive() const { return CurrentHealth > 0; }
	
	// Getters
	int32 GetCurrentHealth() const { return CurrentHealth; }
	int32 GetMaxHealth() const { return MaxHealth; }
};
