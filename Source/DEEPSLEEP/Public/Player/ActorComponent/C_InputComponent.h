// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/ActorComponent/C_StateComponent.h"
#include "C_InputComponent.generated.h"


class UC_DashComponent;
class UC_TargetComponent;
class UC_ReloadComponent;
class AC_BaseWeapon;
class ACharacter;
class AC_PlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_InputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UC_InputComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY()
	AC_PlayerCharacter* PlayerCharacter;

	UPROPERTY()
	TSubclassOf<AC_PlayerCharacter> Player_Class;
	
private:
	UPROPERTY()
	UC_DashComponent* Dash;

	UPROPERTY()
	UC_TargetComponent* Target;

	UPROPERTY()
	UC_ReloadComponent* Reload;

	UPROPERTY()
	AC_BaseWeapon* BaseWeapon;

	UPROPERTY()
	UC_StateComponent* StateComponent;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	EWeaponState WeaponTypeState = EWeaponState::Max;
public:
	//---------Keyboard Eng------------
	void R_key();
	void C_key();
	void Q_key();
	void E_key();
	void T_key();

	//--------Keyboard Num--------------
	void key_1();
	void key_2();
	void key_3();
	


public:
	void MouseRight();
	void MouseLeft();
	
};
