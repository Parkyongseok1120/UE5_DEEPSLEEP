// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvQueryContext_Player.generated.h"

/**
 *  U환경 질의컨텍스트_Player
 *  첫 번째 로컬 플레이어를 반환하는 기본 환경 질의 컨텍스트
 */
UCLASS()
class UEnvQueryContext_Player : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:

	/** context locations or 액터s for this 환경 질의를 제공합니다. */
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
