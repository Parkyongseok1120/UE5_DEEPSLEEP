// Fill out your copyright notice in the Description page of Project Settings.


#include "Traster/C_TrasterBase.h"
#include "Perception/PawnSensingComponent.h"
#include "Util/Global.h"


// Sets default values
AC_TrasterBase::AC_TrasterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AC_TrasterBase::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AC_TrasterBase::OnNoiseHeard);
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));
	
	HP = 100;
}

// Called when the game starts or when spawned
void AC_TrasterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_TrasterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_TrasterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_TrasterBase::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		bIsPlayerSeen = false;
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 35.0f, 13, FColor::Yellow,false, 10.0f);
	bIsPlayerSeen = true;
}

void AC_TrasterBase::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 35.0f, 13, FColor::Red, false, 10.0f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	
	FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	LookAt.Pitch =0.0f;
	LookAt.Roll=0.0f;

	SetActorRotation(LookAt);
}

void AC_TrasterBase::ReceiveDamage(float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	HP -= Damage;
	CLog::Print(HP);
}



