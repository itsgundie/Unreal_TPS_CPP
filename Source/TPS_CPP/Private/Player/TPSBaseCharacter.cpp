// TPS game made in UE4 with CPP and Blueprints


#include "Player/TPSBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/TPSCharacterMovementComponent.h"

// Sets default values
ATPSBaseCharacter::ATPSBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UTPSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

bool ATPSBaseCharacter::isSprinting() const
{
    return isGonnaSprint && isMovingForward && !GetVelocity().IsZero();
}

float ATPSBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;
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
}

// Called every frame
void ATPSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATPSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATPSBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATPSBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ATPSBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ATPSBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATPSBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATPSBaseCharacter::OnStartSprnting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATPSBaseCharacter::OnEndSprinting);
}

void ATPSBaseCharacter::MoveForward(float Amount)
{
    isMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ATPSBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f)
        return;
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
