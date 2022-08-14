// TPS game made in UE4 with CPP and Blueprints


#include "Weapon/TPSBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

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
}

