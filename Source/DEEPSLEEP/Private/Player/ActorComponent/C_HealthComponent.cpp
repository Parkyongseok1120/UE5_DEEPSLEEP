// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_HealthComponent.h"
#include "Player/ActorComponent/C_StateComponent.h"
#include "Player/C_PlayerCharacter.h"
#include "Util/Global.h"


UC_HealthComponent::UC_HealthComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;
	PlayerHP = 100;
	PlayerMental = 100;
	PlayerWillpower = 400;
	
}


void UC_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AC_PlayerCharacter>(GetOwner());
	State = CHelpers::GetComponent<UC_StateComponent>(OwnerCharacter);
	
}


// Called every frame
void UC_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(PlayerHP <= 0)
	{
		Dead();
	}
}

void UC_HealthComponent::OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType)
{
}

void UC_HealthComponent::AutoRecoveryHP()
{
	
}

void UC_HealthComponent::AutoRecoveryWillpower()
{
	
}

void UC_HealthComponent::AutoRecoveryMental()
{
}

void UC_HealthComponent::Dead()
{
	if(State != nullptr)
	{
		State->SetDeadState();
	}
}

