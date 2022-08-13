// TPS game made in UE4 with CPP and Blueprints


#include "Components/TPSHealthComponent.h"

UTPSHealthComponent::UTPSHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}


void UTPSHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
}
