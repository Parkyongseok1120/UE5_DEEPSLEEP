// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "C_PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEEPSLEEP_API UC_PlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	bool bFalling;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	bool bisBackward = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Animation")
	bool bisEqiupWepaon = false;

	bool bEquipFucCall = false;
	
	FRotator PrevRotation; // 이전 회전값.

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void EquipWeapon(bool B_EW);

private:
	class ACharacter* OwnerCharacter;
	class AC_PlayerCharacter* PlayerCharacter;

};
