// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSkillManagement.generated.h"


UENUM(BlueprintType)

enum class EHealthSkill : uint8
{
	Charging = 0, TargetingDash, Return, Parrying, Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FChangeHealthSkillChange, EHealthSkill, InPrevType, EHealthSkill, InNewType);

class ACBaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UCSkillManagement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCSkillManagement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public: //--------------HealthSkill--------
	void SetChargingSkill();
	void SetTargetDashSkill();
	void SetReturnSkill();
	void SetParryingSkill();

private: //--------------Change Skill----------
	void ChangeHealthSkill(EHealthSkill InType);

	//----ENUMS-------
	EHealthSkill HealthSkill;

	//----Delegate
	FChangeHealthSkillChange OnHealthSkillChanged;
	
	UPROPERTY(VisibleAnywhere)
	ACBaseCharacter* OwnerCharacter;
};

