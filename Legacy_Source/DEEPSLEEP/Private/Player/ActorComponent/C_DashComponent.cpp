// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_DashComponent.h"
#include "GameFramework/Character.h"
#include "Player/C_PlayerCharacter.h"
#include "Player/C_DashGhost.h"
#include "Traster/C_TrasterBase.h"
#include "Util/Global.h"

UC_DashComponent::UC_DashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UC_DashComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if(OwnerCharacter)
	{
		PlayerCharacter = Cast<AC_PlayerCharacter>(OwnerCharacter);
		if(PlayerCharacter)
		{
			//PlayerCharacter->OnDashGhostEvent.AddDynamic(this, &UC_DashComponent::BeginDash);
		}
	}
	bCanDash = true;
	bDashOn = false;
}


// Called every frame
void UC_DashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CoolTime += DeltaTime;
	if(CoolTime > 5.0f)
	{
		bCanDash = true;
	}

	if(Traster)
		bTargeting = Traster->GetBisTargeting();
}

void UC_DashComponent::TargetingDash()
{
	CheckNull(OwnerCharacter)
	if(bCanDash != false)
	{
		Traster = Cast<AC_TrasterBase>(UGameplayStatics::GetActorOfClass(GetWorld(), AC_TrasterBase::StaticClass()));
		if(Traster)
		{
			FVector TrasterLocation = Traster->GetActorLocation() + FVector(10,0,0);
			FRotator TrasterRotation = Traster->GetActorRotation();

			OwnerCharacter->SetActorLocation(TrasterLocation, true);
			Traster->SetTargetingNull();
		}
		CoolTime = 0.0f;
		End();
	}
}

void UC_DashComponent::BeginDash()
{
	CheckNull(OwnerCharacter)

	if(bCanDash != false)
	{
		DashPoint();
		if(OwnerCharacter)
		{
			if(PlayerCharacter)
			{
				//PlayerCharacter->StartDashGhost();
			}
		}
		CoolTime = 0.0f;
	}
	
}



void UC_DashComponent::End()
{
	bCanDash = false;
	bDashOn = false;
	//PlayerCharacter->EndDashGhost();
}

void UC_DashComponent::DashPoint()
{
	FVector DashDirection = OwnerCharacter->GetLastMovementInputVector().GetSafeNormal();
	FVector DashOffset = DashDirection * DashDistance;
	OwnerCharacter->AddActorWorldOffset(DashOffset, true);
	
	End();
}

void UC_DashComponent::AttackDashPoint()
{

	
}


