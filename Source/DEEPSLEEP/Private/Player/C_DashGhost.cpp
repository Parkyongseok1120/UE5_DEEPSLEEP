// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/C_DashGhost.h"
#include "Util/Global.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

AC_DashGhost::AC_DashGhost()
{
	CHelpers::CreateComponent<UPoseableMeshComponent>(this, &Mesh, "Mesh");

}

void AC_DashGhost::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "/Script/Engine.MaterialInstanceConstant'/Game/Blueprints/Player/Materials/M_GhostTrail_Inst.M_GhostTrail_Inst'");

	Material = UMaterialInstanceDynamic::Create(material, this);
	Material->SetVectorParameterValue("Color", Color);
	Material->SetScalarParameterValue("Exponent", Exponent);

	Mesh->SetVisibility(false);
	Mesh->SetSkinnedAssetAndUpdate(OwnerCharacter->GetMesh()->GetSkinnedAsset());
	Mesh->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
	Mesh->SetRelativeScale3D(Scale);

	for(int32 i = 0; i <OwnerCharacter->GetMesh()->GetSkinnedAsset()->GetMaterials().Num(); i++)
	{
		Mesh->SetMaterial(i, Material);
	}

	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([&]()
	{
		if(Mesh->IsVisible() == false)
			Mesh->ToggleVisibility();

		SetActorLocation(OwnerCharacter->GetActorLocation() + FVector(0,0,-90));
		SetActorRotation(OwnerCharacter->GetActorRotation() + FRotator(0,-90, 0));

		Mesh->CopyPoseFromSkeletalComponent(OwnerCharacter->GetMesh());
	});
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, timerDelegate, Interval, true, StartDelay);
}

void AC_DashGhost::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

}



