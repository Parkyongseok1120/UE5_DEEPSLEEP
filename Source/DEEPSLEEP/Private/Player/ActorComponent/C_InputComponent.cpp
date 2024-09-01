// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_InputComponent.h"
#include "Util/Global.h"
#include "Player/ActorComponent/C_DashComponent.h"
#include "Player/ActorComponent/C_ReloadComponent.h"
#include "Player/ActorComponent/C_StateComponent.h"
#include "Player/ActorComponent/C_TargetComponent.h"
#include "GameFramework/Character.h"
#include "Player/Weapons/C_BaseWeapon.h"

// Sets default values for this component's properties
UC_InputComponent::UC_InputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UC_InputComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UC_InputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_InputComponent::R_key()
{
}

void UC_InputComponent::C_key()
{
	Dash = GetOwner()->GetComponentByClass<UC_DashComponent>();
	if(Dash != nullptr)
	{
		Dash->BeginDash();
	}
}

void UC_InputComponent::Q_key()
{
}

void UC_InputComponent::E_key()
{
}

void UC_InputComponent::T_key()
{
	Target = GetOwner()->GetComponentByClass<UC_TargetComponent>();
	if(Target != nullptr)
	{
		Target->Toggle();
	}
}

void UC_InputComponent::key_1()
{
	PlayerCharacter = Cast<AC_PlayerCharacter>(GetOwner());
	if(PlayerCharacter != nullptr)
		PlayerCharacter->SpawnWeapon1();
}

void UC_InputComponent::key_2()
{
}

void UC_InputComponent::key_3()
{
}

void UC_InputComponent::MouseRight()
{
	
}

void UC_InputComponent::MouseLeft()
{
	//BaseWeapon = Cast<AC_BaseWeapon>()
}

