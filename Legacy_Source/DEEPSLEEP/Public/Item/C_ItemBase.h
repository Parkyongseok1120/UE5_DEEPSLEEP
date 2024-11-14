// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/ActorComponent/C_InventoryComponent.h"
#include "C_ItemBase.generated.h"

class UC_InventoryComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class DEEPSLEEP_API AC_ItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ItemBase();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	USphereComponent* ItemSphere;

	UFUNCTION()
	virtual void UsingItem(){}


	

public:
	// 아이템을 플레이어가 획득할 때 호출되는 함수
	UFUNCTION(BlueprintCallable, Category = "Item")
	void OnPickedUp();
	
	FInventoryItem GetItemInfo(){return ItemInfo;}
};
