// 에픽게임즈의 모든 권리 보유.


#include "CombatDummy.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ACombatDummy::ACombatDummy()
{
 	PrimaryActorTick.bCanEverTick = true;

	// root 생성
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// base plate 생성
	BasePlate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Plate"));
	BasePlate->SetupAttachment(RootComponent);

	// dummy 생성
	Dummy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dummy"));
	Dummy->SetupAttachment(RootComponent);

	Dummy->SetSimulatePhysics(true);

	// physics constraint 생성
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Physics Constraint"));
	PhysicsConstraint->SetupAttachment(RootComponent);

	PhysicsConstraint->SetConstrainedComponents(BasePlate, NAME_None, Dummy, NAME_None);
}

void ACombatDummy::ApplyDamage(float Damage, AActor* DamageCauser, const FVector& DamageLocation, const FVector& DamageImpulse)
{
	// impulse to dummy 적용
	Dummy->AddImpulseAtLocation(DamageImpulse, DamageLocation);

	// call 블루프린트 handler
	BP_OnDummyDamaged(DamageLocation, DamageImpulse.GetSafeNormal());
}

void ACombatDummy::HandleDeath()
{
	// un사용
}

void ACombatDummy::ApplyHealing(float Healing, AActor* Healer)
{
	// un사용
}

void ACombatDummy::NotifyDanger(const FVector& DangerLocation, AActor* DangerSource)
{
	// un사용
}
