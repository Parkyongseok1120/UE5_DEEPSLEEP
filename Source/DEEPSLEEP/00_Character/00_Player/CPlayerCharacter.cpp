// Fill out your copyright notice in the Description page of Project Settings.

#include "00_Character/00_Player/CPlayerCharacter.h"
#include "00_Character/02_Component/CDashComponent.h"
#include "00_Character/02_Component/CInventoryComponent.h"
#include "00_Character/02_Component/CStateComponent.h"
#include "00_Character/CAnimInstance.h"
#include "00_Character/02_Component/CEnhancedInputComponent.h"
#include "00_Character/02_Component/CGameplayTags.h"

#include "02_Item/CBaseItem.h"
#include "01_Weapon/00_Component/CWeaponManagement.h"
#include "01_Weapon/01_CoreWeapon/CCoreWeapon.h"

#include "EnhancedInput/Public/InputAction.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Global.h"

//=========================================================================================
// 생성자 및 초기화 함수
//=========================================================================================

ACPlayerCharacter::ACPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
      
    DashComponent = CreateDefaultSubobject<UCDashComponent>(TEXT("DashComponent"));
    check(DashComponent);  // 생성 후 즉시 검증
    
    InventoryComponent = CreateDefaultSubobject<UCInventoryComponent>(TEXT("Inventory"));
    WeaponManagement = CreateDefaultSubobject<UCWeaponManagement>(TEXT("WeaponManagement"));
    
    
    // 카메라 설정
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    
    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    PlayerCamera->SetupAttachment(SpringArm);

    // 메쉬 및 스프링암 위치/회전 설정
    GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
    GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
    SpringArm->SetRelativeRotation(FRotator(0, 0, 0));
    SpringArm->SetRelativeLocation(FVector(-18, 63, 49));

    // 캐릭터 무브먼트 설정
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    // 기본 상태 초기화
    bWantsToZoom = false;
    bisSprint = false;
    bCanDoubleJump = true;
}

void ACPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // 초기 설정
    DefaultFOV = PlayerCamera->FieldOfView;
    GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;

     
 
    // 컴포넌트가 없으면 지연 생성 시도
    if (!DashComponent)
    {
        CLog::Log("대시 컴포넌트 없음 - 지연 생성 시도");
        DashComponent = NewObject<UCDashComponent>(this, UCDashComponent::StaticClass(), TEXT("DashComponent"));
        DashComponent->RegisterComponent();
    }
    
    // 이벤트 바인딩
    if (StateComponent)
    {
        StateComponent->OnMovementTypeChanged.AddDynamic(this, &ACPlayerCharacter::OnMovementTypeChanged);
    }
    else
    {
        CLog::Log("StateComponent is NULL in BeginPlay!");
    }
    
    SpringArm->bEnableCameraLag = true;
    
    // 시작 시 무기 숨김
    HideWeapon1();
}

//=========================================================================================
// 기본 오버라이드 함수
//=========================================================================================

void ACPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 카메라 FOV 보간 처리
    float TargetFOV = bWantsToZoom ? ZoomedFOV : DefaultFOV;
    float NewFOV = FMath::FInterpTo(PlayerCamera->FieldOfView, TargetFOV, DeltaTime, ZoomInterpSpeed);
    PlayerCamera->SetFieldOfView(NewFOV);
}

FVector ACPlayerCharacter::GetPawnViewLocation() const
{
    if (PlayerCamera)
    {
        return PlayerCamera->GetComponentLocation();
    }

    return Super::GetPawnViewLocation();
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UCEnhancedInputComponent* CEnhancedInputComponent = Cast<UCEnhancedInputComponent>(PlayerInputComponent);
    check(CEnhancedInputComponent);

    // 기본 이동 및 시야 입력
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Input_Move);
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Input_Look);

    // 공격 입력
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Mouse_Left, ETriggerEvent::Started, WeaponManagement, &UCWeaponManagement::PlayerAtteck);

    // 줌 입력
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Mouse_Right, ETriggerEvent::Started, this, &ACPlayerCharacter::BeginZoom);
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Mouse_Right, ETriggerEvent::Completed, this, &ACPlayerCharacter::EndZoom);

    // 이동 관련 입력
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Jump, ETriggerEvent::Started, this, &ACPlayerCharacter::Jump);
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Sprint, ETriggerEvent::Started, this, &ACPlayerCharacter::BeginSprint);
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Sprint, ETriggerEvent::Completed, this, &ACPlayerCharacter::EndSprint);
    
    // 무기 전환 입력
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_1, ETriggerEvent::Started, this, &ACPlayerCharacter::HideWeapon1);
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_2, ETriggerEvent::Started, this, &ACPlayerCharacter::SpawnHealthCore);
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Key_3, ETriggerEvent::Started, this, &ACPlayerCharacter::SpawnOblivionCore);
    
    // 대시 입력
    CEnhancedInputComponent->BindActionByTag(InputConfig, CGameplayTags::InputTag_Dash, ETriggerEvent::Started, this, &ACPlayerCharacter::DashStart);
}

//=========================================================================================
// 입력 처리 함수
//=========================================================================================

void ACPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
    // 입력 벡터 추출
    FVector2D MovementVector = InputActionValue.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // 컨트롤러 기준 방향 계산
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        // 최종 입력 방향 계산
        FVector InputDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;
        
        // 대시 컴포넌트에 입력 방향 전달
        if (DashComponent)
        {
            DashComponent->SetInputDirection(InputDirection);
        }

        // 이동 입력 적용
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ACPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
    FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
    
    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X / 5);
        AddControllerPitchInput(LookAxisVector.Y / -5);
    }
}

//=========================================================================================
// 무기 관련 함수
//=========================================================================================

void ACPlayerCharacter::SpawnHealthCore()
{
    if (StateComponent)
    {
        StateComponent->SetHealthCoreState();
    }
}

void ACPlayerCharacter::SpawnOblivionCore()
{
    if (StateComponent)
    {
        StateComponent->SetOblivionCoreState();
    }
}

void ACPlayerCharacter::HideWeapon1()
{
    if (StateComponent)
    {
        StateComponent->SetHandsState();
    }
}

void ACPlayerCharacter::AttackEnemy(ACBaseCharacter* Target)
{
    Super::AttackEnemy(Target);
    if (Target)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player attacks!"));
        // Target->TakeDamage(20); // 예시로 20 데미지
    }
}

//=========================================================================================
// 카메라 관련 함수
//=========================================================================================

void ACPlayerCharacter::BeginZoom()
{
    if (bisSprint)
    {
        EndSprint();
    }

    bWantsToZoom = true;
    SpringArm->bEnableCameraLag = false;
}

void ACPlayerCharacter::EndZoom()
{
    bWantsToZoom = false;
    SpringArm->bEnableCameraLag = true;
}

//=========================================================================================
// 움직임 관련 함수
//=========================================================================================

void ACPlayerCharacter::MoveForward(float Value)
{
    if (Value != 0.0f && Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(Direction, Value);
    }
}

void ACPlayerCharacter::MoveRight(float Value)
{
    if (Value != 0.0f && Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(Direction, Value);
    }
}

void ACPlayerCharacter::BeginSprint()
{
    if (!bWantsToZoom)
    {
        bisSprint = true;
        GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
    }
    
    // 대시 컴포넌트에 달리기 상태 전달
    if (DashComponent)
    {
        DashComponent->SetOwnerSprinting(true);
    }
}

void ACPlayerCharacter::EndSprint()
{
    bisSprint = false;
    OnWalk();

    // 대시 컴포넌트에 달리기 종료 상태 전달
    if (DashComponent)
    {
        DashComponent->SetOwnerSprinting(false);
    }
}

void ACPlayerCharacter::OnWalk()
{
    GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
}

void ACPlayerCharacter::Jump()
{
    // 첫 번째 점프
    Super::Jump();
    
    // 더블 점프 처리
    if (!IsGrounded() && bCanDoubleJump)
    {
        LaunchCharacter(FVector(0.0f, 0.0f, JumpForce), false, true);
        bCanDoubleJump = false;
    }

    // 땅에 닿으면 더블 점프 초기화
    if (IsGrounded())
    {
        bCanDoubleJump = true;
    }
}

bool ACPlayerCharacter::IsGrounded() const
{
    FVector Start = GetActorLocation();
    FVector End = Start - FVector(0, 0, 100.0f);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,
        Start,
        End,
        ECC_Visibility,
        QueryParams
    );

    // 디버그 시각화
    DrawDebugLine(
        GetWorld(),
        Start,
        End,
        FColor::Red,
        false,
        1.0f,
        0,
        1.0f
    );
    
    return bHit;
}

//=========================================================================================
// 대시 관련 함수
//=========================================================================================

void ACPlayerCharacter::DashStart()
{
    if (IsValid(DashComponent))  // IsValid 함수로 더 안전하게 확인
    {
        CLog::Log("대시 시작 - 컴포넌트 사용 가능");
        DashComponent->StartDash();
    }
    else
    {
        CLog::Log("오류: DashComponent를 찾을 수 없습니다!");
        
        // 컴포넌트를 찾아 참조 설정 시도
        /*UCDashComponent* FoundComponent = FindComponentByClass<UCDashComponent>();
        if (IsValid(FoundComponent))
        {
            CLog::Log("컴포넌트를 찾아서 참조 설정 시도");
            DashComponent = FoundComponent;
            DashComponent->StartDash();
        }*/
    }
}

//=========================================================================================
// 아이템 관련 함수
//=========================================================================================

void ACPlayerCharacter::InteractWithItem(ACBaseItem* Item)
{
    if (Item || ACBaseItem::StaticClass())
    {
        // 아이템을 인벤토리에 추가
        InventoryComponent->AddItem(Item->GetItemInfo());
        
        // 아이템 획득 후 처리
        Item->OnPickedUp();
    }
}

void ACPlayerCharacter::TryPickupItem()
{
    // 레이캐스트로 아이템 탐지
    FHitResult HitResult;
    FVector Start = GetActorLocation();
    FVector ForwardVector = GetActorForwardVector();
    FVector End = Start + (ForwardVector * 200.0f);

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
    {
        ACBaseItem* HitItem = Cast<ACBaseItem>(HitResult.GetActor());
        
        if (HitItem)
        {
            InteractWithItem(HitItem);
        }
    }
}

//=========================================================================================
// 상태 변경 관련 함수
//=========================================================================================

void ACPlayerCharacter::OnMovementTypeChanged(EMovementState InPrevType, EMovementState InNewType)
{
    // 상태 변경 처리 로직
}

void ACPlayerCharacter::OnSelfStateTypeChanged(ESelfState InPrevType, ESelfState InNewType)
{
    // 자기 상태 변경 처리 로직
}