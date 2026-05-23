// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatActivatable.generated.h"

/**
 *  상호작용 가능 인터페이스
 *  a context-agnostic way of activating, deactivating or toggling 액터s를 제공합니다.
 */
UINTERFACE(MinimalAPI, NotBlueprintable)
class UCombatActivatable : public UInterface
{
	GENERATED_BODY()
};

class ICombatActivatable
{
	GENERATED_BODY()

public:

	/** Interactable Actor를 토글합니다. */
	UFUNCTION(BlueprintCallable, Category="Activatable")
	virtual void ToggleInteraction(AActor* ActivationInstigator) = 0;

	/** Activates Interactable Actor */
	UFUNCTION(BlueprintCallable, Category="Activatable")
	virtual void ActivateInteraction(AActor* ActivationInstigator) = 0;

	/** Interactable Actor를 비활성화합니다. */
	UFUNCTION(BlueprintCallable, Category="Activatable")
	virtual void DeactivateInteraction(AActor* ActivationInstigator) = 0;
};
