// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ActorComponent/C_InputComponent.h"

// Sets default values for this component's properties
UC_InputComponent::UC_InputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UC_InputComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UC_InputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UC_InputComponent::R_key()
{
	
}

void UC_InputComponent::C_key()
{
}

void UC_InputComponent::Q_key()
{
}

void UC_InputComponent::E_key()
{
}

void UC_InputComponent::F_Key()
{
}

