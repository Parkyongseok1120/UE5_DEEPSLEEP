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
    
    // 4방향으로 LineTrace 수행
    TArray<FVector> Directions = {
        DashDirection,                          // 전방
        -DashDirection,                         // 후방
        FVector(-DashDirection.Y, DashDirection.X, 0),  // 우측 (90도 회전)
        FVector(DashDirection.Y, -DashDirection.X, 0)   // 좌측 (-90도 회전)
    };
    
    // 각 방향별 벽 위치 저장
    TArray<FVector> WallLocations;
    
    for (const FVector& Direction : Directions)
    {
        FVector TraceStart = InitialPosition;
        FVector TraceEnd = TraceStart + (Direction * 500.0f);
        
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
        
        // 디버그 라인
        DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f);
        
        if (bHit)
        {
            WallLocations.Add(HitResult.Location);
            DrawDebugPoint(GetWorld(), HitResult.Location, 10.0f, FColor::Green, false, 2.0f);
        }
        else
        {
            WallLocations.Add(InitialPosition + (Direction * 1000.0f));
        }
    }

	if(OwnerCharacter->GetMovementComponent()->IsFalling() == false)
	{
		    OwnerCharacter->LaunchCharacter(DashOffset * 10.0f, true, true);
	}
    
    // 4면의 벽 생성
	if (OwnerCharacter->GetMovementComponent()->Velocity.Size() > 0)// 원하는 값으로 변경
		{
			for (int32 i = 0; i < WallLocations.Num(); i++)
             {
                 FActorSpawnParameters SpawnParams;
                 SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
                 
                 // 벽 회전 설정 (각 방향에 맞게)
                 FRotator WallRotation = Directions[i].Rotation();
                 WallRotation.Yaw += 90.0f;
                 
                 AACDashWall* Wall = GetWorld()->SpawnActor<AACDashWall>(AACDashWall::StaticClass(), 
                                                                    WallLocations[i], 
                                                                    WallRotation, 
                                                                    SpawnParams);
                 
                 if (Wall)
                 {
                     // 벽 제거를 위한 타이머
                     FTimerHandle TimerHandle;
                     GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Wall]()
                     {
                         Wall->Destroy();
                     }, 0.1f, false);
                 }
             }
		}
   
}