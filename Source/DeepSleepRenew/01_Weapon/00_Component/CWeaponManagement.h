// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CWeaponManagement.generated.h"


enum class EWeaponState : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEPRENEW_API UCWeaponManagement : public UActorComponent
{
	GENERATED_BODY()

public:
	FORCEINLINE bool GetHeatlthEquipWeapon(){return HealthbEquipWeapon;}
	FORCEINLINE bool GetOblivionEquipWeapon(){return OblivionEquipWeapon;}
	
	
	// Sets default values for this component's properties
	UCWeaponManagement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;





private:

	class ACCoreWeapon* CoreWeapon;
	class ACPlayerCharacter* Player;
	bool bIsCurrentlyReloading = false;
	
	class UCStateComponent* PlayerStateComponent;

	bool HealthbEquipWeapon;
	
	bool OblivionEquipWeapon;

	bool bSpawnWeapon;

	bool bFireMongtagePlay = false;
	bool bReloadMongtagePlay = false;

	UPROPERTY(VisibleAnywhere, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UCPlayerWidget* PlayerWidget;

	class UCReloadComponent* HealthReloadComponent;


	

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ACCoreWeapon> CoreWeaponClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UParticleSystem* HealthCoreParticleEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UParticleSystem* OblivionCoreParticleEffect;

	class UParticleSystemComponent* CurrentParticleComponent;

	void ChangeWeaponParticleEffect(EWeaponState WeaponState);
	
private:
	UFUNCTION()
	void SetVisibleWeapon();

	UFUNCTION()
	void SetActiveCore();

	UFUNCTION()
	void SpawnWeapon();
	
public:
	UFUNCTION(BlueprintCallable, Category = "State")
	void OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType);

	void CreateHUD();

	void PlayerAtteck();

};
