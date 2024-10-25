// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Trapoint.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class DEEPSLEEP_API AC_Trapoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Trapoint();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditAnywhere, Category = "Sphere")
	USphereComponent *GetSphere;

	UPROPERTY(EditAnywhere, Category = "Sphere")
	USphereComponent *FollowSphere;

	// 플레이어 추적
	AActor* PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 300.0f;


public:
	UFUNCTION()
	void OnDetectionSphereOverlapBegin(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDetectionSphereOverlapEnd(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	void FollowCharacter();
	
};
