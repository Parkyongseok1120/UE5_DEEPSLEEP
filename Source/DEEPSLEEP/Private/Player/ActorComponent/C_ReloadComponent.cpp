// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_ReloadComponent.h"
#include "Player/C_PlayerCharacter.h"
#include "Util/Global.h"


UC_ReloadComponent::UC_ReloadComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	//CHelpers::GetAsset(&ReloadingSound, " ");

	
	
}


// Called when the game starts
void UC_ReloadComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UC_ReloadComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UC_ReloadComponent::Reload()
{
	if(bCanReload != false)
	{
		if (ReloadingSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ReloadingSound, OwnerCharacter->GetActorLocation());
		}
		bisStopShooting = true;
		FTimerHandle ReloadingTimerHandle;
		float ReloadingTime =3.f;

		GetWorld()->GetTimerManager().SetTimer(ReloadingTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			AmmoCount = 0;
			RemainAmmoCount = 30;
			bisStopShooting = false;
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(ReloadingTimerHandle);
		}), ReloadingTime, false); //반복도 여기서 추가 변수를 선언해 설정가능
	}
	bCanReload = false;
}
