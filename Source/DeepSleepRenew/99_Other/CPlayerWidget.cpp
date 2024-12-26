// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Other/CPlayerWidget.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "01_Weapon/CBaseWeapon.h"

#include "AnimNodes/AnimNode_RandomPlayer.h"
#include "Components/TextBlock.h"

#include "Global.h"


void UCPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Weapon = Cast<ACBaseWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), ACBaseWeapon::StaticClass()));
	if (Weapon)
	{
		Weapon->AmmoInfo.AddDynamic(this, &UCPlayerWidget::SetBullet);
		UE_LOG(LogTemp, Log, TEXT("Weapon found and AmmoInfo bound"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon not found"));
	}
}


void UCPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
		
}

void UCPlayerWidget::Init(int32 remainAmmoCount, int32 maxAmmoCount)
{
	SetBullet(remainAmmoCount, maxAmmoCount);
}

void UCPlayerWidget::SetBullet(int32 Current, int32 Max)
{
	FString string = FString::Printf(TEXT("%d/%d"), Current, Max);
	UE_LOG(LogTemp, Log, TEXT("SetBullet called: %s"), *string);
	CurrentBullet->SetText(FText::FromString(string));
}
