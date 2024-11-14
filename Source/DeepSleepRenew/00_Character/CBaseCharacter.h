// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBaseCharacter.generated.h"

class UCStateComponent;
class UCHealthComponent;

UCLASS()
class DEEPSLEEPRENEW_API ACBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Health 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCStateComponent* StateComponent;
	
public:
	// 체력 관련 메서드
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void Heal(int32 HealAmount);
	
	// 상태 확인
	bool IsAlive() const;

	// 공격 메서드 (자식 클래스에서 오버라이드)
	virtual void AttackEnemy(ACBaseCharacter* Target)
	PURE_VIRTUAL(ACBaseCharacter::AttackEnemy, );
	

};
