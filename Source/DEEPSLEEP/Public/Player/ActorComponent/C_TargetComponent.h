// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "C_TargetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_TargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_TargetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



	
private:
	class ACharacter* OwnerCharacter;
	class ACharacter* Target;
	
	


private:
	
	UPROPERTY(EditAnywhere, Category = "Debug")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(EditAnywhere, Category = "Settings")
	class UParticleSystem* ParticleAsset;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float TraceDistance = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float InterpSpeed = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float FinishAngle = 2.0f;

private:
	class UParticleSystemComponent* Particle;
	bool bMovingFocus;
	class ACharacter* GetNearlyFrontAngle(const TArray<FHitResult>& InHitResults);
	
public:
	void Toggle();
	
private:
	void TargetingStart();
	void TargetingEnd();



	
};
