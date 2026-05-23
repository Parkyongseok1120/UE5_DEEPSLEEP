// 프로젝트 설정의 설명 페이지에서 저작권 고지를 작성하세요.


#include "Combat/CombatFNameTags.h"

// 문자열 해시 관리 == FName <- 타입임.
// 유니코드 인코딩 매크로 == TEXT()
// 그냥 섞어 스자.

// 일반적인 const는 선언과 동시에 정의를 하는게 맞지만, 
// static const는 이 클래스의 모든 객체가 공유하는 단 하나의 변수이기 때문에 선언, 정의 분리가 가능.
// 만약 static const FName 변수에 대한 정의를 선언(헤더)에 했다면, 
// 1. 해당 파일 헤더를 include 하는 파일마다 똑같은 변수가 계속 생김. (중복 정의)
// 2. 즉 메모리 낭비가 된다는 이야기이다. 


//CombatTags
const FName FCombatTags::Player = FName(TEXT("Player"));
const FName FCombatTags::Enemy = FName(TEXT("Enemy"));
const FName FCombatTags::Neutral = FName(TEXT("Neutral"));
const FName FCombatTags::Summon = FName(TEXT("Summon"));

//HitDetection
const FName FHitDetection::Melee = FName(TEXT("Melee"));
const FName FHitDetection::Ranged = FName(TEXT("Ranged"));
const FName FHitDetection::AoE = FName(TEXT("AoE"));
const FName FHitDetection::Target = FName(TEXT("Target"));


