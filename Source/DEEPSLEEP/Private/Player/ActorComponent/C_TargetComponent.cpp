// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_TargetComponent.h"
#include "Util/Global.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Player/ActorComponent/C_StateComponent.h"
#include "Traster/C_TrasterBase.h"


// Sets default values for this component's properties
UC_TargetComponent::UC_TargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	CHelpers::GetAsset<UParticleSystem>(&ParticleAsset,"/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'");
}



void UC_TargetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	bisTargeting = false;
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


void UC_TargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(bisTargeting == true)
	{
		TargetingTime += DeltaTime;
		if(TargetingTime > 2.0f)
		{
			TargetingEnd();
			TargetingTime = 0.0f;
		}
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckNull(Target);

	//몬스터가 죽은 상태가 아니라면.
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
	//두 지점사이의 방향 계산으로 회전 값을 반환
	FRotator ownertoTarget = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), Target->GetActorLocation());
	CLog::Print(ownertoTarget);
	
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
		
		CheckNull(Target);
		return;
	}
	TargetingEnd();
}


ACharacter* UC_TargetComponent::GetNearlyFrontAngle(const TArray<FHitResult>& InHitResults)
{
	//백터 내적(플레이어 카메라 각도 cos)
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
	bool bTargetHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), location, location, TraceDistance, "Targeting", false, ignores, DrawDebug, hitResults, true);

	if(bTargetHit)
	{
		for(const FHitResult& Hit : hitResults)
		{
			//Hit된 Actor가 AC_TrasterBase거나, 그 자손일 경우
			AActor* HitActor = Hit.GetActor();
			if(HitActor && HitActor->IsA(AC_TrasterBase::StaticClass()))
			{
				//타겟팅 파티클 생성
				FVector hitActorLocation = HitActor->GetActorLocation();
				FVector particleLocation = hitActorLocation + FVector(0,0,100);
				if(!!Particle)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleAsset, particleLocation);
				}
				bisTargeting = true;
				TargetActor = HitActor;
			}
		}
	}
	

}

void UC_TargetComponent::TargetingEnd()
{
	Target = nullptr;

	if(!!Particle)
		Particle->DestroyComponent();

	bisTargeting = false;
}

void UC_TargetComponent::TargetingDash()
{
	OwnerCharacter->SetActorRelativeLocation(TargetActor->GetActorLocation());
}


