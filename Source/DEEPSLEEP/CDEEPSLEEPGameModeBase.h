// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CDEEPSLEEPGameModeBase.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS()
class DEEPSLEEP_API ACDEEPSLEEPGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACDEEPSLEEPGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	// 블루프린트에서 할당할 위젯 클래스 (예: WBP_PlayerHUD)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	// 실제로 생성된 위젯 인스턴스를 저장할 변수
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentWidget;
};
