#include "CDEEPSLEEPGameModeBase.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h" 

ACDEEPSLEEPGameModeBase::ACDEEPSLEEPGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	if (PlayerPawnBPClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void ACDEEPSLEEPGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerWidgetClass is not set in the GameMode."));
		return;
	}
}

void ACDEEPSLEEPGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}