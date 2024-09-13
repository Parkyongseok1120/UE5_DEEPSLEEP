// Fill out your copyright notice in the Description page of Project Settings.


#include "Traster/C_TrasterBase.h"


// Sets default values
AC_TrasterBase::AC_TrasterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

