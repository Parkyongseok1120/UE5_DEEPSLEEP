// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/CBaseItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Particles/ParticleSystemComponent.h"

#include "Global.h"
#include "00_Character/00_Player/CPlayerCharacter.h"

// Sets default values
ACBaseItem::ACBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &ItemMesh, "ItemMesh");
	CHelpers::CreateComponent<USphereComponent>(this, &ItemSphere, "ItemSphere", ItemMesh);
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &ItemParticleComponent, "ItemParticles", ItemMesh);
	ItemParticleComponent->SetTemplate(ItemParticleEffect);
	
	ItemMesh->SetRelativeScale3D(FVector(1));
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ItemSphere->SetRelativeLocation(FVector(0,0,0));
	ItemSphere->SetSphereRadius(2);

	ItemSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &ACBaseItem::OnOverlapBegin);
	
	// 아이템 기본 정보 설정
	ItemInfo.ItemName = TEXT("Default Item");
	ItemInfo.ItemID = 0;
	ItemInfo.Quantity = 1;
	ItemInfo.ItemDescription = TEXT("Default Item Description");

}

// Called when the game starts or when spawned
void ACBaseItem::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACBaseItem::OnPickedUp()
{

}
void ACBaseItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
									 AActor* OtherActor,
									 UPrimitiveComponent* OtherComp,
									 int32 OtherBodyIndex,
									 bool bFromSweep,
									 const FHitResult& SweepResult)
{
	// 오버랩된 액터가 플레이어 캐릭터인지 확인
	ACPlayerCharacter* PlayerCharacter = Cast<ACPlayerCharacter>(OtherActor);
	CLog::Print("Item On Overlap Begin");
    
	/*if (PlayerCharacter)
	{
        
		// 아이템 제거
		Destroy();
	}*/
}