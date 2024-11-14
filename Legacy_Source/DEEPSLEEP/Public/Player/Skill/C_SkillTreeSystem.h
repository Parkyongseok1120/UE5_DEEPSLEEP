// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_SkillTreeSystem.generated.h"

UENUM(BlueprintType)
enum class EHealthSkillList : uint8
{
	HSkill1 = 0, HSkill2, HSkill3, HSkill4, Max
};

UENUM(BlueprintType)
enum class EOblivionSkillList : uint8
{
	OSkill1 = 0, OSkill2, OSkill3, Max
};

UENUM(BlueprintType)
enum class EUtilSkillList : uint8
{
	USKill1 = 0, USKill2, USKill3, Max
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_SkillTreeSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_SkillTreeSystem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	int32 traPoint = 0;
	bool bisActive = false;

public:
	UFUNCTION(BlueprintCallable)
	void AssignSkill();

	UFUNCTION(BlueprintCallable)
	void SetActiveSkill();

	UFUNCTION(BlueprintCallable)
	void SkillUpgrade();

	UFUNCTION(BlueprintCallable)
	int32 GetTrapoint(){return traPoint;}

	UFUNCTION(BlueprintCallable)
	void SetTraPoint();

	UFUNCTION(BluePrintCallable)
	void GetActiveSkill();
	
};
