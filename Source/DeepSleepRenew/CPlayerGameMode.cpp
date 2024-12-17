// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPlayerGameMode.h"
#include "DeepSleepRenewCharacter.h"
#include "99_Other/CPlayerWidget.h"
#include "UObject/ConstructorHelpers.h"

ACPlayerGameMode::ACPlayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ACPlayerGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Chat UI 위젯 생성
	if (PlayerWidgetClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			
			UCPlayerWidget* Widget = CreateWidget<UCPlayerWidget>(World, PlayerWidgetClass);
			if (Widget)
			{
				Widget->AddToViewport();
				UE_LOG(LogTemp, Warning, TEXT("위젯 생성 및 초기화에 성공했습니다."));

			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("위젯 생성 및 초기화에 실패했습니다."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("월드 컨텍스트가 유효하지 않습니다."));
		}
	}
}

void ACPlayerGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
