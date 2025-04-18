// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CReloadComponent.generated.h"

class ACCoreWeapon;
class ACharacter;
class ACBaseWeapon;
class UCPlayerWidget;

DECLARE_MULTICAST_DELEGATE(FOnReloadStartDelegate);
DECLARE_MULTICAST_DELEGATE(FOnReloadEndDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCReloadComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	FORCEINLINE int32 GetRemainAmmoCount() {return RemainAmmoCount;}
	FOnReloadStartDelegate OnReloadStart;
	FOnReloadEndDelegate OnReloadEnd;

	UFUNCTION()
	bool IsReloading() const { return bReloading; }
	
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
	ACCoreWeapon* CoreWeapon;

	UPROPERTY()
	int32 MaxAmmo;
	
	UPROPERTY()
	int32 UsingAmmoCount;
	
	UPROPERTY()
	int32 RemainAmmoCount;
	
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
	void SetMaxAmmo(int32 CoreSetMaxAmmo);
};

