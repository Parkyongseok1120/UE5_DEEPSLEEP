// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Skill/C_Trapoint.h"

#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Player/C_PlayerCharacter.h"
#include "Util/Global.h"

// Sets default values
AC_Trapoint::AC_Trapoint()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh");
	CHelpers::CreateComponent<USphereComponent>(this, &GetSphere, "GetSphere" ,Mesh);
	CHelpers::CreateComponent<USphereComponent>(this, &FollowSphere, "FollowSphere" ,Mesh);

	Mesh->SetRelativeScale3D(FVector(0.35));
	GetSphere->SetRelativeLocation(FVector(0,0, +45));
	GetSphere->SetRelativeScale3D(FVector(3));
	FollowSphere->SetRelativeLocation(FVector(0,0, +45));

	FollowSphere->OnComponentBeginOverlap.AddDynamic(this, &AC_Trapoint::OnDetectionSphereOverlapBegin);
	FollowSphere->OnComponentEndOverlap.AddDynamic(this, &AC_Trapoint::OnDetectionSphereOverlapEnd);
	

}

// Called when the game starts or when spawned
void AC_Trapoint::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AC_PlayerCharacter>(GetOwner());
	
}

// Called every frame
void AC_Trapoint::Tick(float DeltaTime)
{
	if (PlayerCharacter)
	{
		FVector Direction = (PlayerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + (Direction * MoveSpeed * DeltaTime);
		SetActorLocation(NewLocation);
	}

}

void AC_Trapoint::OnDetectionSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == PlayerCharacter)
	{
		PlayerCharacter = OtherActor;
		CLog::Print("PlayerCharacter");
	}
	
}

void AC_Trapoint::OnDetectionSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CLog::Print("PlayerCharacter");

	if (OtherActor == PlayerCharacter)
	{
		PlayerCharacter = nullptr;
	}
}

void AC_Trapoint::FollowCharacter()
{
	
}

