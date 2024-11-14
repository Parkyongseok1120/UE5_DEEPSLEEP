// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_DashGhost.generated.h"

UCLASS()
class DEEPSLEEP_API AC_DashGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_DashGhost();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = "Capture")
	float StartDelay = 0;

	UPROPERTY(EditAnywhere, Category = "Capture")
	float Interval = 0.25f;

	UPROPERTY(EditAnywhere, Category = "Capture")
	FLinearColor Color = FLinearColor(1,1,1,1);

	UPROPERTY(EditDefaultsOnly, Category = "Capture")
	float Exponent = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Capture")
	FVector Scale = FVector::OneVector;

	UPROPERTY(EditDefaultsOnly, Category= "Capture")
	FVector ScaleAmount = FVector::ZeroVector;


private:
	UPROPERTY(VisibleAnywhere)
	class UPoseableMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;
	class UMaterialInstanceDynamic* Material;

	FTimerHandle TimerHandle;
	
};
