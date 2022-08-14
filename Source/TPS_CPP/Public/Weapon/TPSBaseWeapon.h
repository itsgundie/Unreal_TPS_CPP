// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class TPS_CPP_API ATPSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ATPSBaseWeapon();

    virtual void Fire();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMeshComponent;
};
