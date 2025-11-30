// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/CBaseCharacter.h"
#include "00_Character/02_Component/CHealthComponent.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "Global.h"

// Sets default values
ACBaseCharacter::ACBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UCHealthComponent>(this, &HealthComponent, "HealthComponent");
	CHelpers::CreateActorComponent<UCStateComponent>(this, &StateComponent, "StateComponent");
}

// Called when the game starts or when spawned
void ACBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


float ACBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 1. 부모 클래스의 TakeDamage를 먼저 호출
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 2. 유효성 검사
	if (ActualDamage <= 0.0f)
	{
		return 0.0f;
	}

	// 3. HealthComponent 유효성 검사
	if (HealthComponent != nullptr)
	{
		HealthComponent->TakeDamage(ActualDamage);
	}
	else
	{
		CLog::Print("Healthcomponent nullptr.");
	}

	return ActualDamage;
}

// 회복 처리
void ACBaseCharacter::Heal(int32 HealAmount)
{
	if (HealthComponent)
	{
		HealthComponent->Heal(HealAmount);
	}
}
// 살아있는지 체크
bool ACBaseCharacter::IsAlive() const
{
	return HealthComponent && HealthComponent->IsAlive();
}


