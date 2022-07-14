// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

UCLASS()
class TPS_CPP_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 66.6f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 3.3f;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	int32 WeaponsNum = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 9;
	UPROPERTY(EditInstanceOnly, Category = "Health")
	float Healh = 35.39034f;
	UPROPERTY(EditAnywhere, Category = "Health")
	bool isAlive = true;
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	bool isLoaded = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	FVector InitLocation;
	void printTypes();
	void printStringTypes();
	void printTransform();
};
