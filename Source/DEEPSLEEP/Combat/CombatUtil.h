#pragma once

#include "CoreMinimal.h"
#include "CombatFNameTags.h"
#include "CombatTypes.h"
#include "CombatUtil.generated.h"


USTRUCT()
struct FCombatTypeTagsUtil
{
	GENERATED_BODY()
	
	//------ 해당 태그에 Type파일에 있던 Enum 값 상수 넣기 ------
	static FORCEINLINE FName GetTagFromType(ECombatType Type)
	{
		switch (Type)
		{
		case ECombatType::Player:
			UE_LOG(LogTemp,Warning, TEXT("액터 태그 Player로 확인됨 - FCombatTypeTagsUtil::GetTagFromType."));
			return FCombatTags::Player;
			//break가 리턴과 같이 있으면 어짜피 break 도달 못함.*절대 실행될 일 없음.
		case ECombatType::Enemy:
			UE_LOG(LogTemp,Warning, TEXT("액터 태그 Enemy로 확인. - FCombatTypeTagsUtil::GetTagFromType"));
			return FCombatTags::Enemy;
			
		case ECombatType::Summon:
			UE_LOG(LogTemp,Warning, TEXT("액터 태그 Summon으로 확인.- FCombatTypeTagsUtil::GetTagFromType"));
			return FCombatTags::Summon;
			
		case ECombatType::Neutral:
			UE_LOG(LogTemp,Warning, TEXT("액터 태그 Neutral로 확인. - FCombatTypeTagsUtil::GetTagFromType"));
			return FCombatTags::Neutral;
		}
		
		return NAME_None; //none 예외처리 
	}
	
	//------------ 해당 태그가 맞는지에 대한 검사 함수 ----------
	static FORCEINLINE bool IsEnemy(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FCombatTags::Enemy);
	}
	
	static FORCEINLINE bool IsPlayer(AActor * Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FCombatTags::Player);
	}
	
	static FORCEINLINE bool IsSummon(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FCombatTags::Summon);
	}
	
	static FORCEINLINE bool IsNeutral(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FCombatTags::Neutral);
	}
	
	//---------태그 액터에 세팅하는 함수------------
	
	static FORCEINLINE bool SetCombatType(AActor* Actor, ECombatType NewType)
	{
		if (!IsValid(Actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("액터가 존재하지 않음. - FCombatTypeTagsUtil::SetCombatType"))
			return false;
		}

		//일단 남아있는 태그 전부 지우기
		RemoveCombatTags(Actor);
		
		//새로운 태그가 GetTagFromType을 거쳐 어떤 타입인지 확인.
		const FName NewTags = GetTagFromType(NewType);
		
		//확인 결과 없으면 반환.
		if (NewTags.IsNone())
		{
			UE_LOG(LogTemp, Warning, TEXT("NewTag를 ECombatType에서 찾을 수 없음. - FCombatTypeTagsUtil::SetCombatType" ))
			return false;
		}
		
		Actor->Tags.AddUnique(NewTags);
		return true;
	}
	
	static FORCEINLINE void RemoveCombatTags(AActor* Actor)
	{
		if (!IsValid(Actor))
		{
			UE_LOG(LogTemp, Warning, TEXT("액터가 존재하지 않음. - FCombatTypeTagsUtil::SetCombatType"))
			return;
		}

		//일단 남아있는 태그 전부 지우기
		Actor->Tags.Remove(FCombatTags::Player);
		Actor->Tags.Remove(FCombatTags::Summon);
		Actor->Tags.Remove(FCombatTags::Neutral);
		Actor->Tags.Remove(FCombatTags::Enemy);
	}
	
};

USTRUCT(BlueprintType)
struct FHitDetectionUtil
{
	GENERATED_BODY()
	
	static FORCEINLINE FName GetHitDetection(EHitDetection HitType)
	{
		switch (HitType)
		{
		case EHitDetection::Melee:
			return FHitDetection::Melee;
		case EHitDetection::Ranged:
			return FHitDetection::Ranged;
		case EHitDetection::AoE:
			return FHitDetection::AoE;
		case EHitDetection::Target:
			return FHitDetection::Target;
		}
		
		return NAME_None;
	}
	
	static FORCEINLINE bool IsMelee(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FHitDetection::Melee);
		//대충 리턴문 의미 (아래와 같다)
		/*if (Actor->ActorHasTag(FHitDetection::Melee)) 
		{
			return true;
		}
		return false;*/
	}
	
	static FORCEINLINE bool IsRanged(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FHitDetection::Ranged);
	}
	
	static FORCEINLINE bool IsAoE(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FHitDetection::AoE);
	}
	
	static FORCEINLINE bool IsTarget(AActor* Actor)
	{
		if (!IsValid(Actor))
			return false;
		return Actor->ActorHasTag(FHitDetection::Target);
	}
	
	static FORCEINLINE bool SetHitTags(AActor* Actor, EHitDetection HitType)
	{
		if (!IsValid(Actor))
			return false;
		
		RemoveHitTags(Actor);
		
		const FName NewTags = GetHitDetection(HitType);
		if (NewTags.IsNone())
			return false;
		
		Actor->Tags.AddUnique(NewTags);
		return true;
	}
	
	static FORCEINLINE void RemoveHitTags(AActor* Actor)
	{
		if (!IsValid(Actor))
			return;
		
		Actor->Tags.Remove(FHitDetection::Melee);
		Actor->Tags.Remove(FHitDetection::Ranged);
		Actor->Tags.Remove(FHitDetection::AoE);
		Actor->Tags.Remove(FHitDetection::Target);
	}
};


