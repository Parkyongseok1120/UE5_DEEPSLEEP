// Fill out your copyright notice in the Description page of Project Settings.


#include "CSkillManagement.h"
#include "00_Character/CBaseCharacter.h"
#include "Global.h"

// Sets default values for this component's properties
UCSkillManagement::UCSkillManagement()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCSkillManagement::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACBaseCharacter>(GetOwner());
}


// Called every frame
void UCSkillManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//======================Health Skill==================

void UCSkillManagement::SetChargingSkill()
{
	ChangeHealthSkill(EHealthSkill::Charging);
}

void UCSkillManagement::SetTargetDashSkill()
{
	ChangeHealthSkill(EHealthSkill::TargetingDash);
}

void UCSkillManagement::SetReturnSkill()
{
	ChangeHealthSkill(EHealthSkill::Return);
}

void UCSkillManagement::SetParryingSkill()
{
	ChangeHealthSkill(EHealthSkill::Parrying);
}

void UCSkillManagement::ChangeHealthSkill(EHealthSkill InType)
{
	EHealthSkill prevType = HealthSkill;
	HealthSkill = InType;

	if (OnHealthSkillChanged.IsBound())
		OnHealthSkillChanged.Broadcast(prevType, InType);
}

