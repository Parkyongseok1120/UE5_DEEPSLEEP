// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_DoAttackTrace.generated.h"

/**
 *  액터에게 공격 추적 검사를 수행해 피해 대상을 찾도록 알리는 애님 노티파이입니다.
 */
UCLASS()
class UAnimNotify_DoAttackTrace : public UAnimNotify
{
	GENERATED_BODY()
	
protected:

	/** 공격 추적의 기준 본 */
	UPROPERTY(EditAnywhere, Category="Attack")
	FName AttackBoneName;

public:

	/** 애님 노티파이를 수행합니다. */
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	/** 노티파이 이름을 반환합니다. */
	virtual FString GetNotifyName_Implementation() const override;
};
