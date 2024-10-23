// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_SkillManager.generated.h"

UCLASS()
class DEEPSLEEP_API UC_SkillManager : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UC_SkillManager();

protected:
	// 스킬 실행 중인지 체크
	UPROPERTY()
	bool bIsSkillExecuting;
    
	// 쿨다운 관련 변수
	UPROPERTY()
	float CooldownTime;
    
	// 스킬 데미지 등 기본 속성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float BaseDamage;

	// 기본 함수들
	virtual void BeginPlay() override;
    
public:
	// 스킬 실행 가상 함수
	UFUNCTION(BlueprintCallable, Category = "Skill")
	virtual void ExecuteSkill(){}
    
	// 쿨다운 체크
	UFUNCTION(BlueprintPure, Category = "Skill")
	bool IsSkillReady() const;
    
	// 스킬 종료
	UFUNCTION()
	virtual void EndSkill(){}
};

