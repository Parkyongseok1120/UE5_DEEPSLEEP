// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_SkillManager.h"
#include "Components/ActorComponent.h"
#include "C_HealthSkillComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPSLEEP_API UC_HealthSkillComponent : public UC_SkillManager
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_HealthSkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	FTimerHandle CooldownTimerHandle;

	// 파이어볼 특화 속성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	float FireDuration;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fireball")
	class UParticleSystem* FireballEffect;
    
	// 투사체 클래스
	//UPROPERTY(EditDefaultsOnly, Category = "Fireball")
	//TSubclassOf<class AFireballProjectile> ProjectileClass;

public:
	// 스킬 실행 오버라이드
	virtual void ExecuteSkill() override;
private:
	// 파이어볼 특화 함수들
	void SpawnFireballProjectile();
	void ApplyFireDamage();
};
