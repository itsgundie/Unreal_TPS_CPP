// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TPSCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class TPS_CPP_API UTPSCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.1", ClampMax = "2.5"))
    float SprintModifier = 1.5f;
    virtual float GetMaxSpeed() const override;
};
