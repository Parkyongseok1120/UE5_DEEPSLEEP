// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/CBaseCharacter.h"
#include "CBaseMonster.generated.h"


UCLASS()
class DEEPSLEEPRENEW_API ACBaseMonster : public ACBaseCharacter
{
	GENERATED_BODY()

public:
	ACBaseMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHP;

	UPROPERTY(VisibleAnywhere, Category="Health")
	float CurrentHP;

	bool bisTargeting;
	
	UPROPERTY(VisibleAnywhere, Category="HitCount")
	int32 HitCount = 0;

	UPROPERTY()
	UClass* MonsterAIController;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing")
	bool bIsPlayerSeen;
	
	
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	
	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

public:
	UFUNCTION()
	void SetTargetingNull();
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;	
};

