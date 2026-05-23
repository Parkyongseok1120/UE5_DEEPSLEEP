// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvQueryContext_Danger.generated.h"

/**
 *  U환경 질의컨텍스트_Danger
 *  적 캐릭터의 마지막 위험 위치를 반환합니다.
 */
UCLASS()
class DEEPSLEEP_API UEnvQueryContext_Danger : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:

	/** context locations or 액터s for this 환경 질의를 제공합니다. */
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

};
