// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/00_PlayerItem/CHealthItem.h"

#include "Global.h"


ACHealthItem::ACHealthItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh->SetVisibility(false);
	
	// 아이템 기본 정보 설정
	ItemInfo.ItemName = TEXT("Health Item");
	ItemInfo.ItemID = 1;
	ItemInfo.Quantity = 0;
	ItemInfo.ItemDescription = TEXT("Health Item Description");
}

void ACHealthItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACHealthItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACHealthItem::UsingItem()
{
	Super::UsingItem();
}
