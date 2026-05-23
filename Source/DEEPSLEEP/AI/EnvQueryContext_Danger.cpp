// 에픽게임즈의 모든 권리 보유.


#include "EnvQueryContext_Danger.h"
#include "CombatEnemy.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

void UEnvQueryContext_Danger::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	// querying 적 가져오기
	if (ACombatEnemy* QuerierActor = Cast<ACombatEnemy>(QueryInstance.Owner.Get()))
	{
		// add last recorded danger location to context
		UEnvQueryItemType_Point::SetContextHelper(ContextData, QuerierActor->GetLastDangerLocation());
	}
}