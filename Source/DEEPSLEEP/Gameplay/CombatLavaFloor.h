// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatLavaFloor.generated.h"

class UStaticMeshComponent;
class UPrimitiveComponent;

/**
 *  전투 피해 가능 인터페이스를 통해 접촉 시 피해를 주는 기본 액터입니다. 
 */
UCLASS(abstract)
class ACombatLavaFloor : public AActor
{
	GENERATED_BODY()
	
	/** Floor mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

protected:

	/** Amount of 피해 to deal on contact */
	UPROPERTY(EditAnywhere, Category="Damage")
	float Damage = 10000.0f;

public:	

	/** 생성자 */
	ACombatLavaFloor();

protected:

	/** Blocking hit handler */
	UFUNCTION()
	void OnFloorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
