// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/CHealthComponent.h"
#include "Global.h"

// Sets default values for this component's properties
UCHealthComponent::UCHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 기본 최대 체력 설정
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UCHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UCHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// 데미지 처리
void UCHealthComponent::TakeDamage(float DamageAmount)
{
	// 체력이 0 이하로 내려가지 않도록 처리
	CurrentHealth = FMath::Max(CurrentHealth - DamageAmount, 0);
	if (CurrentHealth == 0)
	{
		
	}
}

// 회복 처리
void UCHealthComponent::Heal(int32 HealAmount)
{
	// 최대 체력 이상으로 회복되지 않도록 처리
	CurrentHealth = FMath::Min(CurrentHealth + HealAmount, MaxHealth);
}
