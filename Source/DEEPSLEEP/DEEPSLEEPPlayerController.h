// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DEEPSLEEPPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  3인칭 게임용 기본 플레이어 컨트롤러 클래스
 *  Manages 입력 mappings
 */
UCLASS(abstract)
class ADEEPSLEEPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping 컨텍스트s */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping 컨텍스트s */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile 제어s 위젯 to s폰 */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to mobile 제어s 위젯 */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, 플레이어 will use 터치 인터페이스 touch 제어s even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** 게임플레이 초기화 */
	virtual void BeginPlay() override;

	/** Input 매핑 컨텍스트 setup */
	virtual void SetupInputComponent() override;

	/** true if 플레이어 should use 터치 인터페이스 touch 제어s를 반환합니다. */
	bool ShouldUseTouchControls() const;

};
