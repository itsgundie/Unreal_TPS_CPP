// TPS game made in UE4 with CPP and Blueprints

#include "Weapon/TPSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogTPSBaseWeapon, All, All);

// Sets default values
ATPSBaseWeapon::ATPSBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMeshComponent");
    SetRootComponent(WeaponMeshComponent);
}

void ATPSBaseWeapon::Fire()
{
    UE_LOG(LogTPSBaseWeapon, Display, TEXT("Incoming Fire!"));
}

void ATPSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
