 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/01_CoreWeapon/CHealthCore.h"
#include "Components/ActorComponent.h"
#include "CBaseSkillComponent.generated.h"

class UCStateComponent;
class UCSkillManagement;

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
	

protected:
	UPROPERTY(EditAnywhere)
	class ACBaseWeapon* OwnerWeapon;
    	
	UPROPERTY(VisibleAnywhere)
	UCStateComponent* PlayerStateComponent;

	UPROPERTY(VisibleAnywhere)
	UCSkillManagement* SkillManagement;

	//아래 자식 클래스에 SkillManagement Enum 델리게이트 추가해야함.

	bool bIsUsingSkill = false;
	bool bisActive = false;

	UFUNCTION()
	virtual void DoSkillAction(){};

	UFUNCTION()
	virtual void SetOwnerWeapon(){};

	UFUNCTION()
	virtual void GetOwnerComponent();
	
};
