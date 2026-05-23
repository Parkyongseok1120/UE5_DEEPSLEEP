// 에픽게임즈의 모든 권리 보유.


#include "CombatDamageableBox.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

ACombatDamageableBox::ACombatDamageableBox()
{
	PrimaryActorTick.bCanEverTick = false;

	// 메시 생성
	RootComponent = Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	// 충돌 속성 설정
	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));

	// 물리 활성화
	Mesh->SetSimulatePhysics(true);

	// 박스가 내비 메시 생성에 영향을 주지 않도록 내비게이션 관련성을 비활성화
	Mesh->bNavigationRelevant = false;
}

void ACombatDamageableBox::RemoveFromLevel()
{
	// destroy this 액터
	Destroy();
}

void ACombatDamageableBox::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 사망 타이머 초기화
	GetWorld()->GetTimerManager().ClearTimer(DeathTimer);
}

void ACombatDamageableBox::ApplyDamage(float Damage, AActor* DamageCauser, const FVector& DamageLocation, const FVector& DamageImpulse)
{
	// 체력이 남아 있을 때만 피해를 처리
	if (CurrentHP > 0.0f)
	{
		// 피해 적용
		CurrentHP -= Damage;

		// 사망했는가?
		if (CurrentHP <= 0.0f)
		{
			HandleDeath();
		}

		// a physics impulse to box, ignoring its mass 적용
		Mesh->AddImpulseAtLocation(DamageImpulse * Mesh->GetMass(), DamageLocation);

		// 효과 재생 등을 위해 블루프린트 핸들러를 호출
		OnBoxDamaged(DamageLocation, DamageImpulse);
	}
}

void ACombatDamageableBox::HandleDeath()
{
	// change collision object type to 가시성 so we ignore most interactions but still retain physics collisions
	Mesh->SetCollisionObjectType(ECC_Visibility);

	// 효과 재생 등을 위해 블루프린트 핸들러를 호출
	OnBoxDestroyed();

	// up death cleanup 타이머 설정
	GetWorld()->GetTimerManager().SetTimer(DeathTimer, this, &ACombatDamageableBox::RemoveFromLevel, DeathDelayTime);
}

void ACombatDamageableBox::ApplyHealing(float Healing, AActor* Healer)
{
	// stub
}

void ACombatDamageableBox::NotifyDanger(const FVector& DangerLocation, AActor* DangerSource)
{
	// stub
}

