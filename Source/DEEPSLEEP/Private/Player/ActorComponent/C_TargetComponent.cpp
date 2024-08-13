// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_TargetComponent.h"
#include "Util/Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/ActorComponent/C_StateComponent.h"


// Sets default values for this component's properties
UC_TargetComponent::UC_TargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	//CHelpers::GetAsset<UParticleSystem>(&ParticleAsset, "");
}



void UC_TargetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


void UC_TargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckNull(Target);

	UC_StateComponent* state = CHelpers::GetComponent<UC_StateComponent>(Target);
	CheckNull(state);
	CheckTrue(state->IsDeadMode());

	float distance = OwnerCharacter->GetDistanceTo(Target);
	if(distance > TraceDistance)
	{
		TargetingEnd();

		return;
	}

	FRotator controlRotation = OwnerCharacter->GetControlRotation();
	FRotator ownertoTarget = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), Target->GetActorLocation());
	ownertoTarget = controlRotation;

	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();

	if(controlRotation.Equals(ownertoTarget, FinishAngle))
	{
		bMovingFocus = false;
		controller->SetControlRotation(ownertoTarget);

		return;
	}

	FRotator targetRotation = FRotator(controlRotation.Pitch, ownertoTarget.Yaw, ownertoTarget.Roll);
	FRotator result = UKismetMathLibrary::RInterpTo(controlRotation, targetRotation, DeltaTime, InterpSpeed);

	controller->SetControlRotation(result);
}

void UC_TargetComponent::Toggle()
{
	if (Target == nullptr)
	{
		TargetingStart();
		

		return;
	}

	TargetingEnd();
}

ACharacter* UC_TargetComponent::GetNearlyFrontAngle(const TArray<FHitResult>& InHitResults)
{
	float angle = -2.0f;
	ACharacter* candidate = nullptr;

	for (int i = 0; i < InHitResults.Num(); i++)
	{
		FVector targetLocation = InHitResults[i].GetActor()->GetActorLocation();

		FVector direction = targetLocation - OwnerCharacter->GetActorLocation();
		direction.Normalize();


		FRotator rotator = OwnerCharacter->GetControlRotation();
		FVector forward = FQuat(rotator).GetForwardVector();

		float dot = FVector::DotProduct(direction, forward);
		if (dot >= angle)
		{
			angle = dot;
			candidate = Cast<ACharacter>(InHitResults[i].GetActor());
		}
	}

	return candidate;
}

void UC_TargetComponent::TargetingStart()
{
	FVector location = OwnerCharacter->GetActorLocation();

	TArray<AActor*> ignores;
	ignores.Add(OwnerCharacter);

	TArray<FHitResult> hitResults;
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), location, location, TraceDistance, "Targeting", false, ignores, DrawDebug, hitResults, true);
}

void UC_TargetComponent::TargetingEnd()
{
	Target = nullptr;

	if(!!Particle)
		Particle->DestroyComponent();
}




