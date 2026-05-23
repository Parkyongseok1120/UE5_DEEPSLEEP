// 에픽게임즈의 모든 권리 보유.


#include "CombatAIController.h"
#include "Components/StateTreeAIComponent.h"

ACombatAIController::ACombatAIController()
{
	// 상태 트리 인공지능 컴포넌트 생성
	StateTreeAI = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAI"));
	check(StateTreeAI);

	// 폰을 빙의할 때 상태 트리가 시작되도록 설정
	bStartAILogicOnPossess = true;

	// 빙의한 캐릭터에 연결되도록 설정
	// 이는 환경 질의가 올바르게 동작하는 데 필요합니다.
	bAttachToPawn = true;
}
