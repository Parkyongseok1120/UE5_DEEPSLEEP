// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CInventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:
	// 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemName;

	// 아이템 ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemID;

	// 아이템 수량
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString ItemDescription;

	// 기본 생성자
	FInventoryItem()
		: ItemName(TEXT("")),
		  ItemID(0),
		  Quantity(1),
		  ItemDescription(TEXT("")) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FInventoryItem> Inventory;

	// 아이템 추가 함수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(const FInventoryItem& NewItem);

	// 아이템 제거 함수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(int32 ItemID);

	// 아이템 존재 확인 함수
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool CheckItem(int32 ItemID) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual void UsingItem(int32 ItemID) {}
	
	
};

