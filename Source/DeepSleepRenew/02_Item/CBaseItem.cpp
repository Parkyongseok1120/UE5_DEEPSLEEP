// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/CBaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Global.h"

// Sets default values
ACBaseItem::ACBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &ItemMesh, "ItemMesh");
	CHelpers::CreateComponent<USphereComponent>(this, &ItemSphere, "ItemSphere", ItemMesh);

	
	ItemMesh->SetRelativeScale3D(FVector(1));
	ItemSphere->SetRelativeLocation(FVector(0,0,+45));
	ItemSphere->SetRelativeScale3D(FVector(2));
	
	// 아이템 기본 정보 설정
	ItemInfo.ItemName = TEXT("Default Item");
	ItemInfo.ItemID = 0;
	ItemInfo.Quantity = 1;
	ItemInfo.ItemDescription = TEXT("Default Item Description");

}

// Called when the game starts or when spawned
void ACBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBaseItem::OnPickedUp()
{

}
