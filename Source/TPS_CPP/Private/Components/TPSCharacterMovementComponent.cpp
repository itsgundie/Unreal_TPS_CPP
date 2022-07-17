// TPS game made in UE4 with CPP and Blueprints


#include "Components/TPSCharacterMovementComponent.h"
#include "Player/TPSBaseCharacter.h"

float UTPSCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ATPSBaseCharacter* Player = Cast<ATPSBaseCharacter>(GetPawnOwner());
    return Player && Player->isSprinting() ? MaxSpeed * SprintModifier : MaxSpeed;
}
