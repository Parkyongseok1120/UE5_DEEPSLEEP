// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_HealthComponent.generated.h"

enum class ESelfState : uint8;
class AC_PlayerCharacter;
class AC_TrasterBase;
class UC_StateComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_HealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	AC_PlayerCharacter* OwnerCharacter;

	UPROPERTY()
	AC_TrasterBase* Traster;
	
	UPROPERTY(VisibleAnywhere)
	UC_StateComponent* State;

	UPROPERTY()//체력
	float PlayerHP;

	UPROPERTY() //정신력
	float PlayerWillpower;

	UPROPERTY()//멘탈수치
	float PlayerMental;

	UFUNCTION(BlueprintCallable, Category = "State")
	void OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType);


public:
	void AutoRecoveryHP();
	void AutoRecoveryWillpower();
	void AutoRecoveryMental();
	void Dead();
	
};


