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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 10000.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float DamageAmount = 10.0f;

    void MakeShot();
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(FHitResult& HitResult);
    virtual void BeginPlay() override;
};
