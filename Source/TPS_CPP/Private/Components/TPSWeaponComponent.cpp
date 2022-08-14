// TPS game made in UE4 with CPP and Blueprints

#include "Components/TPSWeaponComponent.h"
#include "Weapon/TPSBaseWeapon.h"
#include "GameFramework/Character.h"

UTPSWeaponComponent::UTPSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTPSWeaponComponent::Fire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}

void UTPSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapon();
}

void UTPSWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    CurrentWeapon = GetWorld()->SpawnActor<ATPSBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachSocketName);
    CurrentWeapon->SetOwner(GetOwner());
}
