// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/00_Component/CReloadComponent.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"

#include "Global.h"

// Sets default values for this component's properties
UCReloadComponent::UCReloadComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//CHelpers::GetAsset(&ReloadingSound, " ");
	UsingAmmoCount = 0;
	bReloading = false;
}


// Called when the game starts
void UCReloadComponent::BeginPlay()
{
	Super::BeginPlay();
	CoreWeapon = Cast<ACCoreWeapon>(GetOwner());
}


// Called every frame
void UCReloadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCReloadComponent::Reloading()
{
	CheckNull(CoreWeapon);
    
	// 이미 리로딩 중이면 리턴
	if (bReloading)
		return;
        
	bReloading = true; 
	CLog::Print("Reloading Started - bReloading set to true");
	OnReloadStart.Broadcast();  // 리로딩 시작을 알림

	
	if (ReloadingSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadingSound, CoreWeapon->GetActorLocation());
	}
    
	FTimerHandle ReloadingTimerHandle;
	float ReloadingTime = 3.f;

	GetWorld()->GetTimerManager().SetTimer(ReloadingTimerHandle, FTimerDelegate::CreateLambda([this]()
	{
	   if (!CoreWeapon) return;

	   UsingAmmoCount = 0;
	   RemainAmmoCount = MaxAmmo;
	   bisStopShooting = false;

	   CoreWeapon->ReloadComplete(RemainAmmoCount, MaxAmmo);
	   bReloading = false;
		OnReloadEnd.Broadcast();  // 리로딩 완료를 알림

	}), ReloadingTime, false);
}



void UCReloadComponent::AmmoCounting()
{
	UsingAmmoCount++;
	RemainAmmoCount = MaxAmmo - UsingAmmoCount;
}

void UCReloadComponent::SetMaxAmmo(int32 CoreSetMaxAmmo)
{
	MaxAmmo = CoreSetMaxAmmo;
	RemainAmmoCount = MaxAmmo;
}
