// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/C_DashGhost.h"
#include "Player/C_PlayerCharacter.h"
#include "Traster/C_TrasterBase.h"
#include "C_DashComponent.generated.h"

class ACharacter;
class AC_PlayerCharacter;
class UAnimMontage;
class AC_TrasterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_DashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_DashComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	 ACharacter* OwnerCharacter;

	UPROPERTY()
	AC_TrasterBase* Traster;

	UPROPERTY()
	TSubclassOf< AC_PlayerCharacter> PlayerClass;
	
	UPROPERTY()
	AC_PlayerCharacter *PlayerCharacter ;
	
	UPROPERTY()
	UAnimMontage* Anim;

	UPROPERTY()
	bool bCanDash;
	
	UPROPERTY()
	bool bDashOn;

	UPROPERTY()
	bool bTargeting;

	UPROPERTY()
	float DashDistance = 8000.0f;

	int32 DashCount;

	

public:
	UPROPERTY(BlueprintReadOnly, Category="Dash CoolTime")
	float CoolTime;
public:
	void TargetingDash();
	void BeginDash();
	void End();
private:
	void DashPoint();
	void AttackDashPoint();

public:

	
};
