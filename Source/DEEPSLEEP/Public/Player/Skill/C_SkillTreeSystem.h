// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_SkillTreeSystem.generated.h"


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
	bool bisActive_SkillName1;
	bool bisActive_SkillName2;
	bool bisActive_SkillName3;
		
public: 
	bool GetbisActiveSkill();
	bool SetbisActiveSkill();
	
};
