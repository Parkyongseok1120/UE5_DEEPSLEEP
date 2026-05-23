// 에픽게임즈의 모든 권리 보유.


#include "DEEPSLEEPPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "DEEPSLEEP.h"
#include "Widgets/Input/SVirtualJoystick.h"

void ADEEPSLEEPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only s폰 touch 제어s on 로컬 플레이어 제어lers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// s폰 mobile 제어s 위젯
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add 제어s to 플레이어 screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogDEEPSLEEP, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ADEEPSLEEPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add 입력 매핑 컨텍스트s for 로컬 플레이어 제어lers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping 컨텍스트s
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these 입력 매핑 컨텍스트s if we're not using mobile touch 입력
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool ADEEPSLEEPPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
