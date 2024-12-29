// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/00_Component/CWeaponManagement.h"
#include "01_Weapon/01_CoreWeapon/CHealthCore.h"
#include "01_Weapon/01_CoreWeapon/COblivionCore.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/02_Component/CStateComponent.h"

#include "Global.h"
#include "99_Other/CPlayerWidget.h"

// Sets default values for this component's properties
UCWeaponManagement::UCWeaponManagement()
{
	PrimaryComponentTick.bCanEverTick = true;
	Player = Cast<ACPlayerCharacter>(GetOwner());
	
	if (Player)
		PlayerStateComponent = Player->FindComponentByClass<UCStateComponent>();
}

void UCWeaponManagement::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerStateComponent)
	{
		PlayerStateComponent->OnWeaponTypeChanged.AddDynamic(this, &UCWeaponManagement::OnWeaponTypeChanged);
		CLog::Print("WeaponManagement : Loading Success! - Player State Component ");
	}
	else
		CLog::Print("WeaponManagement : Player State Component NULL");
	
	BaseWeapon = Cast<ACBaseWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), ACBaseWeapon::StaticClass()));
}

void UCWeaponManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCWeaponManagement::SetVisibleWeapon()
{
	if (PlayerStateComponent->CheckWeaponState(0) == true) //현재 HandState인지 확인.
	{
		BaseWeapon -> SetActorHiddenInGame(true);
		BaseWeapon -> SetActorEnableCollision(false);
		BaseWeapon -> SetActorTickEnabled(false);
		if (PlayerWidget)
		{
			PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		BaseWeapon->SetActorHiddenInGame(false);
		BaseWeapon->SetActorEnableCollision(true);
		BaseWeapon->SetActorTickEnabled(true);
		
		if (PlayerWidget)
			PlayerWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UCWeaponManagement::SetActiveCore()
{
	if (PlayerStateComponent->CheckWeaponState(0) == true)
	{
		HealthbEquipWeapon = false;
		OblivionEquipWeapon = false;
		CLog::Print("Hand State");
	}
	else if (PlayerStateComponent->CheckWeaponState(1) == true)
	{
		HealthbEquipWeapon = true;
		CLog::Print("HealthCore State");

		if (OblivionEquipWeapon == true)
		{
			OblivionEquipWeapon = false;
			HealthbEquipWeapon = true;
		}
	}
	else if (PlayerStateComponent->CheckWeaponState(2) == true)
	{
		OblivionEquipWeapon = true;
		CLog::Print("Oblivion State");

		if (HealthbEquipWeapon == true)
		{
			HealthbEquipWeapon = false;
			OblivionEquipWeapon = true;
		}
	}
}

void UCWeaponManagement::SpawnWeapon()
{
	bSpawnWeapon = true;
	BaseWeapon = GetWorld()->SpawnActor<ACBaseWeapon>(HealthCoreClass, FVector::ZeroVector, FRotator::ZeroRotator);
	CreateHUD();
				
	if(BaseWeapon)
	{
		BaseWeapon->SetOwner(Player);
		BaseWeapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "FX_Hand_R1");
	}
}

void UCWeaponManagement::CallOnFire()
{
	if (BaseWeapon != nullptr && HealthbEquipWeapon == true || OblivionEquipWeapon == true)
	{
		UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
		UAnimMontage* AnimMontage = Player->GetAnimMontage();
		if(AnimInstance && AnimMontage)
		{
			if (BaseWeapon->GetbisReloading() != true)
			{
				AnimInstance->Montage_Play(AnimMontage);
				BaseWeapon->OnFire(); 
			}
		}
	}
	else
		CLog::Print("Weapon Nullptr");
}

void UCWeaponManagement::OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType)
{
	switch(InNewType)
	{
	case EWeaponState::Hands:
		{
			SetActiveCore();
			if(BaseWeapon)
				SetVisibleWeapon();
			
			break;
		}
	case EWeaponState::HealthCore:
		{
			SetActiveCore();
			if(bSpawnWeapon == true && BaseWeapon)
				SetVisibleWeapon();
			else if (bSpawnWeapon == false && BaseWeapon == nullptr)
				SpawnWeapon();
			
			break;
		}

	case EWeaponState::OblivionCore:
		{
			SetActiveCore();

			if(bSpawnWeapon == true && BaseWeapon)
				SetVisibleWeapon();
			else if (bSpawnWeapon == false && BaseWeapon == nullptr)
				SpawnWeapon();
			
			break;
		}
	}
}

void UCWeaponManagement::CreateHUD()
{
	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UCPlayerWidget>(GetWorld(), PlayerWidgetClass); // 수정된 부분

		if (PlayerWidget)
		{
			HealthCore = NewObject<ACHealthCore>(this);
			int32 Current= HealthCore->GetCurrentAmmo();
			int32 Max = HealthCore->GetMaxAmmo();

			CLog::Print(Current);
			CLog::Print(Max);

			PlayerWidget->Init(Current,Max);
			PlayerWidget->AddToViewport();
			PlayerWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}




