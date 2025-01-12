// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/CDashComponent.h"
#include "00_Character/02_Component/ACDashWall.h"

#include "Global.h"
#include "GameFramework/Character.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/01_Monster/CBaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"


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
   FVector InitialPosition = OwnerCharacter->GetActorLocation();
   FVector DashDirection = OwnerCharacter->GetLastMovementInputVector().GetSafeNormal();
   FVector DashOffset = DashDirection * DashDistance;
   
   float LineLength = 200.0f;      // 감지 범위
   float WallDistance = 1000.0f;    // 벽 생성 거리
   
   // 8방향으로 LineTrace 수행
   TArray<FVector> Directions = {
       DashDirection,                                    // 정면 (0도)
       FVector(-DashDirection.Y, DashDirection.X, 0),    // 우측 (90도)
       -DashDirection,                                   // 후면 (180도)
       FVector(DashDirection.Y, -DashDirection.X, 0),    // 좌측 (270도)
       
       // 대각선 방향들
       (DashDirection + FVector(-DashDirection.Y, DashDirection.X, 0)).GetSafeNormal(),    // 우측 앞 (45도)
       (DashDirection + FVector(DashDirection.Y, -DashDirection.X, 0)).GetSafeNormal(),    // 좌측 앞 (315도)
       (-DashDirection + FVector(-DashDirection.Y, DashDirection.X, 0)).GetSafeNormal(),   // 우측 뒤 (135도)
       (-DashDirection + FVector(DashDirection.Y, -DashDirection.X, 0)).GetSafeNormal()    // 좌측 뒤 (225도)
   };
   
   // 각 방향별 충돌 여부 저장
   TArray<bool> WallCollisions;
   
   for (const FVector& Direction : Directions)
   {
       FVector TraceStart = InitialPosition;
       FVector TraceEnd = TraceStart + (Direction * LineLength);
       
       FHitResult HitResult;
       FCollisionQueryParams QueryParams;
       QueryParams.AddIgnoredActor(OwnerCharacter);
       
       bool bHit = GetWorld()->LineTraceSingleByChannel(
           HitResult,
           TraceStart,
           TraceEnd,
           ECC_Visibility,
           QueryParams
       );
       
       DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
       
       if (bHit)
       {
           WallCollisions.Add(true);
           DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Green, false, 2.0f);
       }
       else
       {
           WallCollisions.Add(false);
       }
   }

   if(!OwnerCharacter->GetMovementComponent()->IsFalling())
   {
       OwnerCharacter->LaunchCharacter(DashOffset * 10.0f, true, true);
   }
   
   // 8면의 벽 생성
   if (OwnerCharacter->GetMovementComponent()->Velocity.Size() > 0)
   {
       for (int32 i = 0; i < Directions.Num(); i++)
       {
           // 충돌된 위치에는 벽을 생성하지 않음
           if (!WallCollisions[i])
           {
               FVector WallLocation = InitialPosition + (Directions[i] * WallDistance);
               
               FActorSpawnParameters SpawnParams;
               SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
               
               FRotator WallRotation = Directions[i].Rotation();
               WallRotation.Yaw += 90.0f;
               
               AACDashWall* Wall = GetWorld()->SpawnActor<AACDashWall>(
                   AACDashWall::StaticClass(), 
                   WallLocation,
                   WallRotation, 
                   SpawnParams
               );
               
               if (Wall)
               {
                   FTimerHandle TimerHandle;
                   GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Wall]()
                   {
                       Wall->Destroy();
                   }, 0.1f, false);
               }
           }
       }
   }
	bCanDash = false;

}