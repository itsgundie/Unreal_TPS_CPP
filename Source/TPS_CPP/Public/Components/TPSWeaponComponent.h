// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TPSWeaponComponent.generated.h"

class ATPSBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPS_CPP_API UTPSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTPSWeaponComponent();

    void Fire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ATPSBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachSocketName = "WeaponSocket";

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ATPSBaseWeapon* CurrentWeapon = nullptr;

    void SpawnWeapon();
};
