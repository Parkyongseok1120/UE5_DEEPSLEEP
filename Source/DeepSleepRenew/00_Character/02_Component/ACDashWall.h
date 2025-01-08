// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACDashWall.generated.h"

UCLASS()
class DEEPSLEEPRENEW_API AACDashWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACDashWall();

protected:
	virtual void BeginPlay() override;
    
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

};
