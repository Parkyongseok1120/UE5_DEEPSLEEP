#include "Player/Skill/C_HealthSkillComponent.h"
#include "Util/Global.h"

UC_HealthSkillComponent::UC_HealthSkillComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
}


void UC_HealthSkillComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UC_HealthSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_HealthSkillComponent::ExecuteSkill()
{
	Super::ExecuteSkill();

	if (!IsSkillReady())
		return;

	Super::ExecuteSkill();
    
	// 발사체 생성
	SpawnFireballProjectile();
    
	// 파티클 효과 재생
	if (FireballEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			FireballEffect,
			GetOwner()->GetActorLocation(),
			GetOwner()->GetActorRotation()
		);
	}
    
	// 쿨다운 시작
	GetWorld()->GetTimerManager().SetTimer(
		CooldownTimerHandle,
		this,
		&UC_HealthSkillComponent::EndSkill,
		CooldownTime,
		false
	);
}

void UC_HealthSkillComponent::SpawnFireballProjectile()
{
}

void UC_HealthSkillComponent::ApplyFireDamage()
{
}


