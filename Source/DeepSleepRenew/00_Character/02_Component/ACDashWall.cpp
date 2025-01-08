// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/ACDashWall.h"

#include "Components/BoxComponent.h"

// Sets default values
AACDashWall::AACDashWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
	// 충돌 박스 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
    
	// 박스 크기 설정 (높이 200, 폭 500, 두께 10)
	CollisionBox->SetBoxExtent(FVector(500.0f, 250.0f, 100.0f));
	CollisionBox->SetVisibility(true);
    
	// 충돌 설정
	CollisionBox->SetCollisionProfileName(TEXT("BlockAll"));

}

// Called when the game starts or when spawned
void AACDashWall::BeginPlay()
{
	Super::BeginPlay();
	
}



