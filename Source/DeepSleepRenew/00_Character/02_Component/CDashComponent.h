// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CDashComponent.generated.h"

//델리게이트 추가 예정.
class ACPlayerCharacter;
class ACBaseMonster;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCDashComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY()
	class ACBaseMonster* Traster;

	UPROPERTY()
	TSubclassOf<ACPlayerCharacter> PlayerClass;
	
	UPROPERTY()
	ACPlayerCharacter *PlayerCharacter ;
	
	UPROPERTY()
	UAnimMontage* Anim;

	UPROPERTY()
	bool bCanDash;
	
	UPROPERTY()
	bool bDashOn;

	UPROPERTY()
	bool bTargeting;

	UPROPERTY()
	float DashDistance = 1000.0f;

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
