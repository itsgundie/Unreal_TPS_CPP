// TPS game made in UE4 with CPP and Blueprints

#include "Weapon/TPSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPSBaseWeapon, All, All);

// Sets default values
ATPSBaseWeapon::ATPSBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
    SetRootComponent(WeaponMeshComponent);
}

void ATPSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponMeshComponent);
}

void ATPSBaseWeapon::Fire()
{
    MakeShot();
}

APlayerController* ATPSBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;
    return Player->GetController<APlayerController>();
}

bool ATPSBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) false;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ATPSBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMeshComponent->GetSocketLocation(MuzzleSocketName);
}

bool ATPSBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ATPSBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;
    
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ATPSBaseWeapon::MakeDamage(FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}

void ATPSBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    float MaxPossibleAngleBetweenTargetAndMuzzle = 70.0f;
    const FVector ActualTraceEnd = HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
    const FVector HitDirectionFromMuzzle = (ActualTraceEnd - GetMuzzleWorldLocation()).GetSafeNormal();
    auto AngleBetweenHitAndMuzzle = FMath::Acos(FVector::DotProduct(GetMuzzleWorldLocation(), HitDirectionFromMuzzle));
    const float AngleInDegrees = FMath::Abs(FMath::RadiansToDegrees(AngleBetweenHitAndMuzzle));
    if (AngleInDegrees > MaxPossibleAngleBetweenTargetAndMuzzle) return;
    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), ActualTraceEnd, FColor::Red, false, 3.0f, 0, 3);
        DrawDebugSphere(GetWorld(), ActualTraceEnd, 13.0f, 24, FColor::Red, false, 5.0f);
        UE_LOG(LogTPSBaseWeapon, Display, TEXT("BONE %s HAS BEEN HIT!"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), ActualTraceEnd, FColor::Red, false, 3.0f, 0, 3);
    }
}
