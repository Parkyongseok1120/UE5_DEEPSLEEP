// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Skill/C_SkillTreeSystem.h"
#include "util/Global.h"

UC_SkillTreeSystem::UC_SkillTreeSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UC_SkillTreeSystem::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void UC_SkillTreeSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

bool UC_SkillTreeSystem::GetbisActiveSkill()
{

    return true;
}

bool UC_SkillTreeSystem::SetbisActiveSkill()
{
    return true;
}

