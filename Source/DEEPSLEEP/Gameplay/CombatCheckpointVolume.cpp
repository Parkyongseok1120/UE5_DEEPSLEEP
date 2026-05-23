// 에픽게임즈의 모든 권리 보유.


#include "CombatCheckpointVolume.h"
#include "Character/DEEPSLEEPCharacter.h"
#include "DEEPSLEEPPlayerController.h"

ACombatCheckpointVolume::ACombatCheckpointVolume()
{
	// 박스 볼륨 생성
	RootComponent = Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	check(Box);

	// 박스 크기 설정
	Box->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));

	// 기본 충돌 프로필을 모든 동적 오버랩으로 설정
	Box->SetCollisionProfileName(FName("OverlapAllDynamic"));

	// 오버랩 시작 이벤트 바인딩 
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACombatCheckpointVolume::OnOverlap);
}

void ACombatCheckpointVolume::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 이 기능이 한 번만 사용되도록 확인
	if (bCheckpointUsed)
	{
		return;
	}
		
	// 플레이어가 이 볼륨에 들어왔는가?
	ACharacter* PlayerCharacter = Cast<ADEEPSLEEPCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		if (ADEEPSLEEPPlayerController* PC = Cast<ADEEPSLEEPPlayerController>(PlayerCharacter->GetController()))
		{
			// 체크포인트 사용 플래그 설정
			bCheckpointUsed = true;

			// 플레이어의 리스폰 체크포인트 갱신
			//PC->SetRes폰Transform(PlayerCharacter->GetActorTransform());
		}

	}
}
