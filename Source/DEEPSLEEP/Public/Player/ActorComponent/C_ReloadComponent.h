// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_ReloadComponent.generated.h"

class ACharacter;
class AC_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_ReloadComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	FORCEINLINE bool GetbCanReload() {return bCanReload;}
	FORCEINLINE int GetRemainAmmoCount() {return RemainAmmoCount;}

public:	
	UC_ReloadComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	AC_BaseWeapon* OwnerWeapon;
	
	UPROPERTY()
	int32 AmmoCount;
	
	UPROPERTY()
	int32 RemainAmmoCount;

	UPROPERTY()
	bool bCanReload;

	UPROPERTY()
	bool bisStopShooting;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sound")
	USoundBase* ReloadingSound;

public:
	void Reloading();
		
};
