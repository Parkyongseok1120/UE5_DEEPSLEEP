// 에픽게임즈의 모든 권리 보유.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatActivationVolume.generated.h"

class UBoxComponent;

/**
 *  플레이어 폰이 들어오면 액터 목록을 활성화하는 단순 볼륨입니다.
 */
UCLASS()
class ACombatActivationVolume : public AActor
{
	GENERATED_BODY()

	/** Collision box volume */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;
	
protected:

	/** List of 액터s to activate 때 이 볼륨 is entered */
	UPROPERTY(EditAnywhere, Category="Activation Volume")
	TArray<AActor*> ActorsToActivate;

public:	
	
	/** 생성자 */
	ACombatActivationVolume();

protected:

	/** 오버랩s with box volume를 처리합니다. */
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
