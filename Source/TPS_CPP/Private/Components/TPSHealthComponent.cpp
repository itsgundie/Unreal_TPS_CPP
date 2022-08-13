// TPS game made in UE4 with CPP and Blueprints


#include "Components/TPSHealthComponent.h"
#include "Player/TPSBaseCharacter.h"
#include "Dev/TPSFireDamageType.h"
#include "Dev/TPSIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(TPSHealthComponentLog, All, All);

UTPSHealthComponent::UTPSHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}

void UTPSHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UTPSHealthComponent::OnTakeAnyDamage);
    }
}

void UTPSHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(TPSHealthComponentLog, Display, TEXT("Damage: %f"), Damage);

    if (DamageType)
    {
        if (DamageType->IsA<UTPSFireDamageType>())
        {
            UE_LOG(TPSHealthComponentLog, Display, TEXT("Burn, Baby, Burn!"));
        }
        else if (DamageType->IsA<UTPSIceDamageType>())
        {
            UE_LOG(TPSHealthComponentLog, Display, TEXT("You are Cold ass Ice, Baby!"));
        }
    }
}
