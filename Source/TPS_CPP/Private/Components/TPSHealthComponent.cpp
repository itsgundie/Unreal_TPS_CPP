// TPS game made in UE4 with CPP and Blueprints

#include "Components/TPSHealthComponent.h"
#include "Player/TPSBaseCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(TPSHealthComponentLog, All, All);

UTPSHealthComponent::UTPSHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTPSHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTPSHealthComponent::OnTakeAnyDamage);
    }
}

void UTPSHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UTPSHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void UTPSHealthComponent::HealUpdate()
{
    SetHealth(Health + HealRate);
    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UTPSHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
