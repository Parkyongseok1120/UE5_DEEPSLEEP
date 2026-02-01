#pragma once

#include "CoreMinimal.h"
#include "CombatTypes.generated.h"

//notice : 해당 코드는 졸업작품 PD(김동인님)의 피드백을 토대로 공부를 위해 제작중인 코드입니다.

//Type에서는 전역 범위관련만 넣어야함. 즉,enum의 목적에 맞지 않게 작동하는 애들은 넣지말것.SSOT


//피아식별
UENUM(BlueprintType)
enum class ECombatType : uint8
{
	Player UMETA(DisplayName = "Player"),				//주인공 플레이어 캐릭터
	Enemy UMETA(DisplayName = "Enemies"),			//적들
	Summon UMETA(DisplayName = "PlayerSummon"),	    //플레이어가 생성한 오브젝트(터렛등등)
	Neutral UMETA(DisplayName = "Neutral")			//중립 NPC 및 오브젝트
};


//공격 판정방식
UENUM(BlueprintType)
enum class EHitDetection : uint8
{
	Melee UMETA(DisplayName = "Melee"),				//근접 공격 -> 회피 유도
	Ranged UMETA(DisplayName = "Ranged"),			//원거리 공격
	Target UMETA(DisplayName = "Target"),			//타겟 공격(확정공격) -> 패링유도
	AoE UMETA(DisplayName = "AoE"),					//광범위
};