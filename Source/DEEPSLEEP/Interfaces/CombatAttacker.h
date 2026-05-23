// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatAttacker.generated.h"

/**
 *  전투 공격자 인터페이스
 *  공격 애니메이션 이벤트를 트리거하기 위한 공통 기능을 제공합니다.
 */
UINTERFACE(MinimalAPI, NotBlueprintable)
class UCombatAttacker : public UInterface
{
	GENERATED_BODY()
};

class ICombatAttacker
{
	GENERATED_BODY()

public:

	/** 공격의 충돌 검사를 수행합니다. 보통 몽타주의 애님 노티파이에서 호출됩니다. */
	UFUNCTION(BlueprintCallable, Category="Attacker")
	virtual void DoAttackTrace(FName DamageSourceBone) = 0;

	/** 콤보 공격이 이어질지 검사합니다. 보통 몽타주의 애님 노티파이에서 호출됩니다. */
	UFUNCTION(BlueprintCallable, Category="Attacker")
	virtual void CheckCombo() = 0;

	/** 차지 공격 애니메이션을 반복할지 검사합니다. 보통 몽타주의 애님 노티파이에서 호출됩니다. */
	UFUNCTION(BlueprintCallable, Category="Attacker")
	virtual void CheckChargedAttack() = 0;
};
