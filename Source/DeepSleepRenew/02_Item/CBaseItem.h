// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "00_Character/02_Component/CInventoryComponent.h"
#include "CBaseItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DEEPSLEEPRENEW_API ACBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	FInventoryItem ItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
	USphereComponent* ItemSphere;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
	class UParticleSystemComponent* ItemParticleComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	class UParticleSystem* ItemParticleEffect;
	
	UFUNCTION()
	virtual void UsingItem(){}

public:
	// 아이템을 플레이어가 획득할 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnPickedUp();
	
	FInventoryItem GetItemInfo(){return ItemInfo;}

	// 오버랩 이벤트 처리 함수
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
					   AActor* OtherActor,
					   UPrimitiveComponent* OtherComp,
					   int32 OtherBodyIndex,
					   bool bFromSweep,
					   const FHitResult& SweepResult);



};
