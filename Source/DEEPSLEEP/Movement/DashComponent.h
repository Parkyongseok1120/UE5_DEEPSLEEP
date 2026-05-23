#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEEPSLEEP_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDashComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category="Dash")
	bool TryDash(const FVector& WorldDirection);

	UFUNCTION(BlueprintPure, Category="Dash")
	bool IsDashing() const { return bIsDashing; }

	UFUNCTION(BlueprintPure, Category="Dash")
	bool IsOnCooldown() const;

protected:
	void EndDash();
	bool CanDash() const;
	FVector ResolveDashDirection(const FVector& WorldDirection) const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true", ClampMin="0"))
	float DashSpeed = 1600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true", ClampMin="0.01", Units="s"))
	float DashDuration = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true", ClampMin="0", Units="s"))
	float DashCooldown = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true"))
	bool bCanDashInAir = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true"))
	bool bPreserveVerticalVelocity = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true", ClampMin="0"))
	float GroundFrictionWhileDashing = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dash", meta=(AllowPrivateAccess="true", ClampMin="0"))
	float BrakingFrictionFactorWhileDashing = 0.0f;

	bool bIsDashing = false;
	float DashEndTime = 0.0f;
	float NextDashAllowedTime = 0.0f;

	float CachedGroundFriction = 0.0f;
	float CachedBrakingFrictionFactor = 0.0f;
};

