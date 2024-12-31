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

	CLog::Print("Reloading");
	bReloading = true;
	
	if (ReloadingSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadingSound, CoreWeapon->GetActorLocation());
	}
	FTimerHandle ReloadingTimerHandle;
	float ReloadingTime =3.f;

	GetWorld()->GetTimerManager().SetTimer(ReloadingTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		UsingAmmoCount = 0;
		RemainAmmoCount = MaxAmmo;
		bisStopShooting = false;
		bReloading = false;
		// TimerHandle 초기화
		GetWorld()->GetTimerManager().ClearTimer(ReloadingTimerHandle);
		CoreWeapon->ReloadComplete(RemainAmmoCount, MaxAmmo);
	}),ReloadingTime, false);//반복도 여기서 추가 변수를 선언해 설정가능
	
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
