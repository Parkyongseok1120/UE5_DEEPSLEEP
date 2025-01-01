// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Weapon/00_Component/CWeaponManagement.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"
#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "01_Weapon/00_Component/CReloadComponent.h"

#include "Global.h"
#include "99_Other/CPlayerWidget.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UCWeaponManagement::UCWeaponManagement()
{
	PrimaryComponentTick.bCanEverTick = true;
	

}

void UCWeaponManagement::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ACPlayerCharacter>(GetOwner());

	if (Player)
		PlayerStateComponent = GetOwner()->FindComponentByClass<UCStateComponent>();
	
	if (PlayerStateComponent)
	{
		PlayerStateComponent->OnWeaponTypeChanged.AddDynamic(this, &UCWeaponManagement::OnWeaponTypeChanged);
		CLog::Print("WeaponManagement : Loading Success! - Player State Component ");
	}
	else
		CLog::Print("WeaponManagement : Player State Component NULL");
	// ReloadComponent가 제대로 초기화되었는지 확인
	
}

void UCWeaponManagement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCWeaponManagement::SetVisibleWeapon()
{
	if (PlayerStateComponent->CheckWeaponState(0) == true) //현재 HandState인지 확인.
	{
		CoreWeapon -> SetActorHiddenInGame(true);
		CoreWeapon -> SetActorEnableCollision(false);
		CoreWeapon -> SetActorTickEnabled(false);
		if (PlayerWidget)
		{
			PlayerWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else
	{
		CoreWeapon->SetActorHiddenInGame(false);
		CoreWeapon->SetActorEnableCollision(true);
		CoreWeapon->SetActorTickEnabled(true);
		
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
		CoreWeapon = GetWorld()->SpawnActor<ACCoreWeapon>(CoreWeaponClass,FVector::ZeroVector, FRotator::ZeroRotator);
	}
	if (CoreWeapon)
	{
		if (Player != nullptr)
		{
			CoreWeapon->SetOwner(Player);
			if (CoreWeapon->GetOwner() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("CoreWeapon owner is NULL after SetOwner(Player)"));
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("CoreWeapon owner set successfully"));
			}
		
			CoreWeapon->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "FX_Hand_R1");
			CreateHUD();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Player is NULL when setting owner for CoreWeapon"));
		}
		HealthReloadComponent = CoreWeapon->FindComponentByClass<UCReloadComponent>();

		if (!HealthReloadComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("ReloadComponent not found in CoreWeapon!"));
		}
		else
		{
			HealthReloadComponent->OnReloadStart.AddLambda([this]()
			{
				bIsCurrentlyReloading = true;
			});

			HealthReloadComponent->OnReloadEnd.AddLambda([this]()
			{
				bIsCurrentlyReloading = false;
			});
		}
	}
	
}

void UCWeaponManagement::PlayerAtteck()
{
	if (CoreWeapon)
	{
		if (Player)
		{
			UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
			UAnimMontage* FireAnimMontage = Player->GetFireAnimMontage();
			UAnimMontage* ReloadAnimMontage = Player->GetReloadAnimMontage();
			if(AnimInstance && FireAnimMontage)
			{
				if (!bIsCurrentlyReloading)  // 로컬 변수로 상태 체크
				{
					CLog::Print("Weapon not Reloading");
					AnimInstance->Montage_Play(FireAnimMontage);
					CoreWeapon->OnFire(Player);
				}
				else
				{
					CLog::Print("Weapon Reloading");
					if (AnimInstance && ReloadAnimMontage)
					{
						
						AnimInstance->Montage_Play(ReloadAnimMontage);
					}
				}
			}
		}
	}
	else
	{
		CLog::Print("Weapon is nullptr in PlayerAtteck!");
	}
}

void UCWeaponManagement::OnWeaponTypeChanged(EWeaponState InPrevType, EWeaponState InNewType)
{
	switch(InNewType)
	{
	case EWeaponState::Hands:
		{
			SetActiveCore();
			if(CoreWeapon)
				SetVisibleWeapon();
			ChangeWeaponParticleEffect(EWeaponState::Hands);

			break;
		}
	case EWeaponState::HealthCore:
		{
			SetActiveCore();
			if(bSpawnWeapon == true && CoreWeapon)
				SetVisibleWeapon();
			else if (bSpawnWeapon == false && CoreWeapon == nullptr)
				SpawnWeapon();
			ChangeWeaponParticleEffect(EWeaponState::HealthCore);

			break;
		}

	case EWeaponState::OblivionCore:
		{
			SetActiveCore();

			if(bSpawnWeapon == true && CoreWeapon)
				SetVisibleWeapon();
			else if (bSpawnWeapon == false && CoreWeapon == nullptr)
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

		if (PlayerWidget && CoreWeapon)  // 기존 CoreWeapon 사용
		{
			
			if (PlayerStateComponent->CheckWeaponState(1) == true || PlayerStateComponent->CheckWeaponState(2) == true)
			{
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
	if (!CoreWeapon)
	{
		CLog::Print("CoreWeapon is null");
		return;
	}

	if (!CoreWeapon->GetWeaponMesh())
	{
		CLog::Print("WeaponMesh is null");
		return;
	}

	// 이전 파티클 시스템 제거
	if (CurrentParticleComponent)
	{
		CurrentParticleComponent->DestroyComponent();
		CLog::Print("Previous particle destroyed");
	}

	UParticleSystem* NewParticleEffect = nullptr;

	// 파티클 효과 선택
	switch (WeaponState)
	{
	case EWeaponState::HealthCore:
		NewParticleEffect = HealthCoreParticleEffect;
		if (!HealthCoreParticleEffect)
			CLog::Print("HealthCoreParticleEffect is null");
		break;
        
	case EWeaponState::OblivionCore:
		NewParticleEffect = OblivionCoreParticleEffect;
		if (!OblivionCoreParticleEffect)
			CLog::Print("OblivionCoreParticleEffect is null");
		break;
	}

	// 파티클 효과 적용
	if (NewParticleEffect)
	{
		CurrentParticleComponent = UGameplayStatics::SpawnEmitterAttached(
			NewParticleEffect, 
			CoreWeapon->GetWeaponMesh(), 
			FName("Muzzle")
		);

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