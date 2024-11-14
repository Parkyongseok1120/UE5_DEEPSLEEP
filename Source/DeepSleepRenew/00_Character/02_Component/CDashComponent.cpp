// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/CDashComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/01_Monster/CBaseMonster.h"

// Sets default values for this component's properties
UCDashComponent::UCDashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UCDashComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if(OwnerCharacter)
	{
		PlayerCharacter = Cast<ACPlayerCharacter>(OwnerCharacter);
		if(PlayerCharacter)
		{
			//PlayerCharacter->OnDashGhostEvent.AddDynamic(this, &UC_DashComponent::BeginDash);
		}
	}
	bCanDash = true;
	bDashOn = false;
}


// Called every frame
void UCDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	CoolTime += DeltaTime;
	if(CoolTime > 5.0f)
	{
		bCanDash = true;
	}

	//if(Traster)  <--------델리게이트로 바꿔야함.
		//bTargeting = Traster->GetBisTargeting();
}

void UCDashComponent::TargetingDash()
{
	CheckNull(OwnerCharacter)
	if(bCanDash != false)
	{
		Traster = Cast<ACBaseMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), ACBaseMonster::StaticClass()));
		if(Traster)
		{
			FVector TrasterLocation = Traster->GetActorLocation() + FVector(10,0,0);
			FRotator TrasterRotation = Traster->GetActorRotation();

			OwnerCharacter->SetActorLocation(TrasterLocation, true);
			//Traster->SetTargetingNull(); <--------델리게이트로 바꿔야함.
		}
		CoolTime = 0.0f;
		End();
	}
}

void UCDashComponent::BeginDash()
{
	CheckNull(OwnerCharacter)

	if(bCanDash != false)
	{
		DashPoint();
		if(OwnerCharacter)
		{
			if(PlayerCharacter)
			{
				//PlayerCharacter->StartDashGhost(); <--------델리게이트로 바꿔야함.
			}
		}
		CoolTime = 0.0f;
	}
	
}



void UCDashComponent::End()
{
	bCanDash = false;
	bDashOn = false;
	//PlayerCharacter->EndDashGhost(); <--------델리게이트로 바꿔야함.
}

void UCDashComponent::DashPoint()
{
	FVector DashDirection = OwnerCharacter->GetLastMovementInputVector().GetSafeNormal();
	FVector DashOffset = DashDirection * DashDistance;
	OwnerCharacter->AddActorWorldOffset(DashOffset, true);
	
	End();
}