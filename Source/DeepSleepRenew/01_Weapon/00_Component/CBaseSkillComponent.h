// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CBaseSkillComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCBaseSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCBaseSkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FORCEINLINE bool CheckisUsing() const { return bIsUsingSkill; }
	virtual FORCEINLINE bool CheckisActive() const { return bisActive; }
	
private:
	UPROPERTY(VisibleAnywhere)
	class ACBaseWeapon* OwnerWeapon;
	
protected:
	UPROPERTY(VisibleAnywhere)
	class UCStateComponent* PlayerStateComponent;

	UPROPERTY(VisibleAnywhere)
	class UCSkillManagement* SkillManagement;

	bool bIsUsingSkill = false;
	bool bisActive = false;

	UFUNCTION()
	virtual void DoSkillAction(){};

	UFUNCTION()
	virtual void SetOwnerWeapon();

	UFUNCTION()
	virtual void GetOwnerComponent();
	
};
