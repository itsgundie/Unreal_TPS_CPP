// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPSBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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
};
