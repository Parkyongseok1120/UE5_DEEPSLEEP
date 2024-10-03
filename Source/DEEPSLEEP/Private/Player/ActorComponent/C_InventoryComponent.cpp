#include "Player/ActorComponent/C_InventoryComponent.h"

UC_InventoryComponent::UC_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


void UC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_InventoryComponent::AddItem(const FInventoryItem& NewItem)
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

void UC_InventoryComponent::RemoveItem(int32 ItemID)
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

bool UC_InventoryComponent::CheckItem(int32 ItemID) const
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

void UC_InventoryComponent::UsingItem(int32 ItemID)
{
	
}

