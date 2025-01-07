// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/CBaseItem.h"
#include "CHealthItem.generated.h"

UCLASS()
class DEEPSLEEPRENEW_API ACHealthItem : public ACBaseItem
{
	GENERATED_BODY()

public:
	ACHealthItem();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void UsingItem() override;

	class UParticleSystemComponent* CurrentParticleComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UParticleSystem* HealthCoreParticleEffect;
	
};
