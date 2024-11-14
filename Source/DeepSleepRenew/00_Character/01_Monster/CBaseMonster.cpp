// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/CBaseMonster.h"
#include "Perception/PawnSensingComponent.h"
#include "Global.h"


ACBaseMonster::ACBaseMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ACBaseMonster::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &ACBaseMonster::OnNoiseHeard);
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
}

void ACBaseMonster::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;
	bisTargeting = false;
}

void ACBaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACBaseMonster::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		bIsPlayerSeen = false;
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 35.0f, 13, FColor::Yellow,false, 10.0f);
	bIsPlayerSeen = true;
}


void ACBaseMonster::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 35.0f, 13, FColor::Red, false, 10.0f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	
	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAt.Pitch =0.0f;
	LookAt.Roll=0.0f;

	SetActorRotation(LookAt);
}

void ACBaseMonster::SetTargetingNull()
{
	bisTargeting = false;
	HitCount = 0;
}

float ACBaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
