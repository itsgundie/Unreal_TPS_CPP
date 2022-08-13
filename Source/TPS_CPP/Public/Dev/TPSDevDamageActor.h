// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSDevDamageActor.generated.h"

UCLASS()
class TPS_CPP_API ATPSDevDamageActor : public AActor
{
    GENERATED_BODY()

public:
    ATPSDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SphereRadius = 314.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SphereDamage = 1.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool SphereDoFullDamage = false;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
