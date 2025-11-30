// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Weapon/00_Component/CBaseSkillComponent.h"
#include "CHealthSkillComponent.generated.h"


UCLASS()
class DEEPSLEEP_API UCHealthSkillComponent : public UCBaseSkillComponent
{
	GENERATED_BODY()

public:
	UCHealthSkillComponent();

protected:
	virtual void BeginPlay() override;
	virtual void SetOwnerWeapon() override;

private:
	
	
};
