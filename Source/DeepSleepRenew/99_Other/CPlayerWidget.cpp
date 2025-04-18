// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Other/CPlayerWidget.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"

#include "Components/TextBlock.h"

#include "Global.h"


void UCPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CoreWeapon = Cast<ACCoreWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), ACCoreWeapon::StaticClass()));
	CurrentBullet = Cast<UTextBlock>(GetWidgetFromName(TEXT("CurrentBullet")));

	// 디버깅용 로그 추가
	if(CurrentBullet)
	{
		UE_LOG(LogTemp, Log, TEXT("CurrentBullet initialized successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentBullet is nullptr"));
	}
		

	if (CoreWeapon)
	{
		CoreWeapon->AmmoInfo.AddDynamic(this, &UCPlayerWidget::SetBullet);
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
	if(!CurrentBullet)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentBullet is nullptr"));
		return;
	}
	FString string = FString::Printf(TEXT("%d/%d"), Current, Max);
	UE_LOG(LogTemp, Log, TEXT("SetBullet called: %s"), *string);
	CurrentBullet->SetText(FText::FromString(string));
}
