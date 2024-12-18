// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPlayerWidget.generated.h"

class UTextBlock;
class UCReloadComponent;

UCLASS()
class DEEPSLEEPRENEW_API UCPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SetBullet(int32 Current, int32 Max)const;

	void Init(int32 remainAmmoCount, int32 maxAmmoCount) const;
	

protected:
	UPROPERTY(BlueprintReadOnly,Category ="TEXT", meta = (BindWidget, AllowPrivateAccess = "true"))
	UTextBlock* CurrentBullet;

	UPROPERTY()
	UCReloadComponent* ReloadComponent;
	
	
	

};
