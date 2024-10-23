#include "Player/Skill/C_HealthSkillComponent.h"

UC_HealthSkillComponent::UC_HealthSkillComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UC_HealthSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UC_HealthSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

