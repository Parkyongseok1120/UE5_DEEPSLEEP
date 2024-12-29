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
	{
		CLog::Print("WeaponManagement : Player State Component NULL");
	}
	BaseWeapon = Cast<ACBaseWeapon>(UGameplayStatics::GetActorOfClass(GetWorld(), ACBaseWeapon::StaticClass()));
}

void UCWeaponManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UCWeaponManagement::SetVisibleWeapon()
{

	BaseWeapon->SetActorHiddenInGame(false);
	BaseWeapon->SetActorEnableCollision(true);
	BaseWeapon->SetActorTickEnabled(true);
	
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
	if (BaseWeapon != nullptr && HealthbEquipWeapon == true || OblivionEquipWeapon)
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
	{
		CLog::Print("Weapon Nullptr");
	}

}

void UCWeaponManagement::OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType)
{

	switch(InNewType)
	{
	case EWeaponState::Hands:
		{
			HealthbEquipWeapon = false;
			OblivionEquipWeapon = false;

			if(BaseWeapon)
			{
				BaseWeapon -> SetActorHiddenInGame(true);
				BaseWeapon -> SetActorEnableCollision(false);
				BaseWeapon -> SetActorTickEnabled(false);
				CLog::Print("Hand State");
				if (PlayerWidget)
				{
					PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
				}
			}
			break;
		}
	case EWeaponState::HealthCore:
		{
			CLog::Print("HealthCore State");

			if(bSpawnWeapon == true && BaseWeapon)
			{
				if (OblivionEquipWeapon == true)
					OblivionEquipWeapon = false;
				
				SetVisibleWeapon();
				HealthbEquipWeapon = true;
				if (PlayerWidget)
				{
					PlayerWidget->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else if (BaseWeapon == nullptr)
			{
				if (OblivionEquipWeapon == true)
					OblivionEquipWeapon = false;
				
				HealthbEquipWeapon = true;
				bSpawnWeapon = true;

				SpawnWeapon();
			}
			break;
		}

	case EWeaponState::OblivionCore:
		{
			if(bSpawnWeapon == true)
			{
				if (HealthbEquipWeapon == true)
					HealthbEquipWeapon = false;
				
				SetVisibleWeapon();
				OblivionEquipWeapon = true;
				if (PlayerWidget)
				{
					PlayerWidget->SetVisibility(ESlateVisibility::Visible);
				}
			}
			else if (BaseWeapon == nullptr)
			{
				if (HealthbEquipWeapon == true)
					HealthbEquipWeapon = false;
				
				OblivionEquipWeapon = true;
				SpawnWeapon();
			}
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




