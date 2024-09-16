// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_TrasterBase.generated.h"

class UPawnSensingComponent;

UCLASS()
class DEEPSLEEP_API AC_TrasterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_TrasterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, Category="Health")
	float HP;

	UPROPERTY()
	UClass* MonsterAIController;

	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sensing")
	bool bIsPlayerSeen;
	
	
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	
	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

public:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void ReceiveDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser);


	
};
