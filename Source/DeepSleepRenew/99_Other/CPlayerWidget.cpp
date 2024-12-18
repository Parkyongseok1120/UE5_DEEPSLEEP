// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Other/CPlayerWidget.h"
#include "Global.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "01_Weapon/00_Component/CReloadComponent.h"
#include "01_Weapon/CBaseWeapon.h"
#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "Components/TextBlock.h"

void UCPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AActor* OwnerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACBaseWeapon::StaticClass());
	if (OwnerActor)
	{
		ReloadComponent = OwnerActor->FindComponentByClass<UCReloadComponent>();
		if (ReloadComponent)
		{
			// 델리게이트 바인딩
			ReloadComponent->BulletInfo.AddDynamic(this, &UCPlayerWidget::SetBullet);
		}
	}

	

	
}

void UCPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
		
}

void UCPlayerWidget::Init(int32 remainAmmoCount, int32 maxAmmoCount) const
{
	SetBullet(remainAmmoCount, maxAmmoCount);
}

void UCPlayerWidget::SetBullet(int32 Current, int32 Max) const
{
	FString string = FString::Printf(TEXT("%d/%d"), Current, Max);
	CurrentBullet->SetText(FText::FromString(string));
}
