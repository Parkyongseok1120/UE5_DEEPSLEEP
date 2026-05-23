// 에픽게임즈의 모든 권리 보유.


#include "CombatActivationVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "CombatActivatable.h"

ACombatActivationVolume::ACombatActivationVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	// 박스 볼륨 생성
	RootComponent = Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	check(Box);

	// 박스 크기 설정
	Box->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));

	// 기본 충돌 프로필을 모든 동적 오버랩으로 설정
	Box->SetCollisionProfileName(FName("OverlapAllDynamic"));

	// 오버랩 시작 이벤트 바인딩 
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACombatActivationVolume::OnOverlap);
}

void ACombatActivationVolume::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// has a Character entered the volume?
	ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);

	if (PlayerCharacter)
	{
		// is Character 제어led by a 플레이어
		if (PlayerCharacter->IsPlayerControlled())
		{
			// process 액터s to activate list
			for (AActor* CurrentActor : ActorsToActivate)
			{
				// is the referenced actor activatable?
				if(ICombatActivatable* Activatable = Cast<ICombatActivatable>(CurrentActor))
				{
					Activatable->ActivateInteraction(PlayerCharacter);
				}
			}
		}
	}

}