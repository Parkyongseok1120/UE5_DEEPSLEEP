

#pragma once

#include "NativeGameplayTags.h" 

/**
 * 해당 태그는 Bp 및 DA에서 모두 많이 씀.
 */

struct FCombatTags
{
	static const FName Player;
	static const FName Summon;
	static const FName Enemy;
	static const FName Neutral;
};

struct FHitDetection
{
	static const FName Melee;
	static const FName Ranged;
	static const FName Target;
	static const FName AoE;
};