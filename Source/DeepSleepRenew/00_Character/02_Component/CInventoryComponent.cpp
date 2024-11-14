// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/CInventoryComponent.h"

// Sets default values for this component's properties
UCInventoryComponent::UCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;


}


void UCInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UCInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UCInventoryComponent::AddItem(const FInventoryItem& NewItem)
{
	// 인벤토리에 같은 아이템이 있는지 확인
	for (FInventoryItem& Item : Inventory)
	{
		if (Item.ItemID == NewItem.ItemID)
		{
			// 이미 존재하는 아이템이면 수량만 증가
			Item.Quantity += NewItem.Quantity;
			return;
		}
	}
}

void UCInventoryComponent::RemoveItem(int32 ItemID)
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].ItemID == ItemID)
		{
			// 수량이 1보다 크면 수량만 감소, 그렇지 않으면 아이템 삭제
			if (Inventory[i].Quantity > 1)
			{
				Inventory[i].Quantity--;
			}
			else
			{
				Inventory.RemoveAt(i);
			}
			return;
		}
	}
}

bool UCInventoryComponent::CheckItem(int32 ItemID) const
{
	for (const FInventoryItem& Item : Inventory)
	{
		if (Item.ItemID == ItemID)
		{
			return true; // 아이템이 존재하면 true 반환
		}
	}
	return false; // 존재하지 않으면 false 반환

}




