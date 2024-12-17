// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CReloadComponent.generated.h"

class ACharacter;
class ACBaseWeapon;
class UCPlayerWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReceiveBulletInfo, int32, CurrentBullet, int32, MaxBullet );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCReloadComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetbReloading() {return bReloading;}
	FORCEINLINE int GetRemainAmmoCount() {return RemainAmmoCount;}

	// 델리게이트 인스턴스
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FReceiveBulletInfo BulletInfo;;
public:	
	// Sets default values for this component's properties
	UCReloadComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	ACBaseWeapon* OwnerWeapon;

	UPROPERTY()
	int32 MaxAmmo;
	
	UPROPERTY()
	int32 UsingAmmoCount;
	
	UPROPERTY()
	int32 RemainAmmoCount;

	UPROPERTY()
	bool bReloading;

	UPROPERTY()
	bool bisStopShooting;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundBase* ReloadingSound;

	UPROPERTY()
	UCPlayerWidget* PlayerWidget;

public:
	void Reloading();
	void AmmoCounting();
};
