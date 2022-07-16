// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementType MoveType = EMovementType::Static;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 66.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Frequency = 3.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
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
	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const {return GeometryData;}

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	
	FOnTimerFinished OnTimerFinished;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data")
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
