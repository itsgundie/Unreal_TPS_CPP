// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UTPSHealthComponent;
class UTextRenderComponent;
class UTPSWeaponComponent;

UCLASS()
class TPS_CPP_API ATPSBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ATPSBaseCharacter(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool isSprinting() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTPSHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 5.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTPSWeaponComponent* WeaponComponent;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    bool isGonnaSprint = false;
    bool isMovingForward = false;
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartSprnting();
    void OnEndSprinting();
    void OnDeath();
    void OnHealthChanged(float Health) const;

    UFUNCTION()
    void OnGroundLanded(const FHitResult& HitResult);
};
