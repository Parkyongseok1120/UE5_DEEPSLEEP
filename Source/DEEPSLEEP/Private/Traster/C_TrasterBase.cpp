// Fill out your copyright notice in the Description page of Project Settings.


#include "Traster/C_TrasterBase.h"

#include "Elements/Columns/TypedElementAlertColumns.h"
#include "Perception/PawnSensingComponent.h"
#include "Util/Global.h"
#include "Engine/DamageEvents.h"


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
	
	MaxHP = 1000;
}

// Called when the game starts or when spawned
void AC_TrasterBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentHP = MaxHP;
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

void AC_TrasterBase::AttackCheck()
{
	
}

float AC_TrasterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 데미지 처리 로직
	CurrentHP -= DamageAmount;

	// 피격 횟수 증가
	HitCount++;
	CLog::Print(HitCount);
	CLog::Print(CurrentHP);

	if (CurrentHP <= 0)
	{
		// 사망 처리
		//Die();
	}

	return CurrentHP;
}



