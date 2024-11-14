// Fill out your copyright notice in the Description page of Project Settings.
#include "Player/Skill/C_SkillManager.h"
#include "Util/Global.h"


UC_SkillManager::UC_SkillManager()
{
}

void UC_SkillManager::BeginPlay()
{
	Super::BeginPlay();
}

bool UC_SkillManager::IsSkillReady() const
{
	return true;
}
