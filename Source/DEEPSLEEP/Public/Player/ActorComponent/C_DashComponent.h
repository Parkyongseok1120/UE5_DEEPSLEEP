// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_DashComponent.generated.h"


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
	class ACharacter* OwnerCharacter;
	
	UPROPERTY()
	class UAnimMontage* Anim;

	UPROPERTY()
	bool bCanDash;

	UPROPERTY()
	float DashDistance = 10000.0f;

public:
	UPROPERTY()
	float Cooltime;
public:
	void BeginDash();
private:
	void EndDash();
	void DashPoint();
	
	
	
};
