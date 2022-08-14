// TPS game made in UE4 with CPP and Blueprints

#include "Dev/TPSDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ATPSDevDamageActor::ATPSDevDamageActor()
{
    PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ATPSDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

void ATPSDevDamageActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(
        GetWorld(), SphereDamage, GetActorLocation(), SphereRadius, DamageType, {}, this, nullptr, SphereDoFullDamage);
}
