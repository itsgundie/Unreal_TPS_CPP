// TPS game made in UE4 with CPP and Blueprints

#include "Player/TPSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TPSCharacterMovementComponent.h"
#include "Components/TPSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/TPSWeaponComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(TPSBaseCharacterLog, All, All);

// Sets default values
ATPSBaseCharacter::ATPSBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UTPSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 100.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UTPSHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<UTPSWeaponComponent>("WeaponComponent");
}

bool ATPSBaseCharacter::isSprinting() const
{
    return isGonnaSprint && isMovingForward && !GetVelocity().IsZero();
}

float ATPSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormalized = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormalized));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormalized);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

// Called when the game starts or when spawned
void ATPSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());
    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ATPSBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ATPSBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ATPSBaseCharacter::OnGroundLanded);
}

// Called every frame
void ATPSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATPSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    check(WeaponComponent);
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATPSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATPSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ATPSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ATPSBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATPSBaseCharacter::OnStartSprnting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATPSBaseCharacter::OnEndSprinting);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UTPSWeaponComponent::Fire);
}

void ATPSBaseCharacter::MoveForward(float Amount)
{
    isMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ATPSBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ATPSBaseCharacter::OnStartSprnting()
{
    isGonnaSprint = true;
}

void ATPSBaseCharacter::OnEndSprinting()
{
    isGonnaSprint = false;
}

void ATPSBaseCharacter::OnDeath()
{
    UE_LOG(TPSBaseCharacterLog, Display, TEXT("Player %s is Dead"), *GetName());
    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ATPSBaseCharacter::OnHealthChanged(float Health) const
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ATPSBaseCharacter::OnGroundLanded(const FHitResult& HitResult)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    UE_LOG(TPSBaseCharacterLog, Display, TEXT("On Landed: %f"), FallVelocityZ);

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(TPSBaseCharacterLog, Display, TEXT("Final Damage: %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
