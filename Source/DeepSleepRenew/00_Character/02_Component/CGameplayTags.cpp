// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/CGameplayTags.h"

#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FCGameplayTags FCGameplayTags::GameplayTags;

UE_DEFINE_GAMEPLAY_TAG(InputTag_Ju, "InputTag.Ju");
UE_DEFINE_GAMEPLAY_TAG(InputTag_M, "InputTag.M");

void FCGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FCGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Move, "InputTag.Move", "Move input.");
	AddTag(InputTag_Look_Mouse, "InputTag.Look.Mouse", "Look (mouse) input.");
	AddTag(InputTag_Look_Stick, "InputTag.Look.Stick", "Look (stick) input.");
	AddTag(InputTag_Jump, "InputTag.Jump", "Jump input");
	AddTag(InputTag_Fire, "InputTag.Fire", "Fire input.");
}

void FCGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
