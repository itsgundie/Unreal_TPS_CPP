// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType: uint8
{
	Sin,
	Static
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 66.6f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 3.3f;

	UPROPERTY(EditAnywhere, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float TimerRateSec = 2.5f;
};

UCLASS()
class TPS_CPP_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	void SetGeometryData(const FGeometryData& Data) {GeometryData = Data;}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Geometry Data")
	FGeometryData GeometryData;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;
	
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 9;
	
	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Health = 35.39034f;
	
	UPROPERTY(EditAnywhere, Category = "Health")
	bool isAlive = true;
	
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool isLoaded = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FVector InitLocation;
	FTimerHandle TimerHandle;
	const int32 MaxTimerCount = 7;
	int32 TimerCount = 0;
	void PrintTypes();
	void PrintStringTypes();
	void PrintTransform();
	void HandleMovement();
	void SetColor(const FLinearColor& Color);
	void OnTimerFired();
};
