// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_CheckChargedAttack.generated.h"

/**
 *  차지 공격 홀드 여부를 검사하는 애님 노티파이입니다.
 */
UCLASS()
class UAnimNotify_CheckChargedAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	/** 애님 노티파이를 수행합니다. */
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	/** 노티파이 이름을 반환합니다. */
	virtual FString GetNotifyName_Implementation() const override;
};
