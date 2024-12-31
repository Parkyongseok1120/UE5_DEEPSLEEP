// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/00_Component/CWeaponManagement.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/02_Component/CStateComponent.h"

#include "Global.h"
#include "99_Other/CPlayerWidget.h"
#include "Particles/ParticleSystemComponent.h"

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
	if (PlayerStateComponent->CheckWeaponState(1) == true || PlayerStateComponent->CheckWeaponState(2) == true)
	{
		BaseWeapon = GetWorld()->SpawnActor<ACBaseWeapon>(CoreWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}
	if(BaseWeapon)
	{
		BaseWeapon->SetOwner(Player);
		BaseWeapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "FX_Hand_R1");
		CreateHUD();
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
			ChangeWeaponParticleEffect(EWeaponState::HealthCore);

			break;
		}

	case EWeaponState::OblivionCore:
		{
			SetActiveCore();

			if(bSpawnWeapon == true && BaseWeapon)
				SetVisibleWeapon();
			else if (bSpawnWeapon == false && BaseWeapon == nullptr)
				SpawnWeapon();
			ChangeWeaponParticleEffect(EWeaponState::OblivionCore);

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
			
			if (PlayerStateComponent->CheckWeaponState(1) == true || PlayerStateComponent->CheckWeaponState(2) == true)
			{
				CoreWeapon = NewObject<ACCoreWeapon>(this);
				int32 HealthCoreCurrent= CoreWeapon->GetCurrentAmmo();
				int32 HealthCoreMax = CoreWeapon->GetMaxAmmo();

				CLog::Print(HealthCoreCurrent);
				CLog::Print(HealthCoreMax);

				PlayerWidget->Init(HealthCoreCurrent, HealthCoreMax);
				PlayerWidget->AddToViewport();
				PlayerWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
		}
	}
	else
	{
		CLog::Print("No Player Widget Class");
	}
}

void UCWeaponManagement::ChangeWeaponParticleEffect(EWeaponState WeaponState)
{
	// 이전 파티클 시스템 제거
	if (CurrentParticleComponent)
	{
		CurrentParticleComponent->DestroyComponent();
	}

	UParticleSystem* NewParticleEffect = nullptr;

	// 파티클 효과 선택
	switch (WeaponState)
	{
	case EWeaponState::Hands:
		if (CurrentParticleComponent)
		{
			CurrentParticleComponent->DestroyComponent();
		}
		break;
		
	case EWeaponState::HealthCore:
		NewParticleEffect = HealthCoreParticleEffect;
		break;
		
	case EWeaponState::OblivionCore:
		NewParticleEffect = OblivionCoreParticleEffect;
		break;
	default:
		break;
	}

	// 파티클 효과 적용
	if (NewParticleEffect)
	{
		// 파티클을 손에 부착 (예: 무기 소켓에 부착)
		CurrentParticleComponent = UGameplayStatics::SpawnEmitterAttached(NewParticleEffect, BaseWeapon->GetWeaponMesh(), FName("MuzzleLocation"));
		switch (WeaponState)
		{
		case EWeaponState::HealthCore:
			CurrentParticleComponent->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));
			break;
			
		case EWeaponState::OblivionCore:
			CurrentParticleComponent->SetRelativeScale3D(FVector(0.4f,0.4f,0.4f));
			break;
		default:
			break;
		}
	}
}