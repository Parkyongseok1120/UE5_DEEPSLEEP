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

public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	class ACharacter* OwnerCharacter;
	
};
