// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i=0; i < 10; ++i)
		{
			const FTransform GeometryActorTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 451.0f * i, 451.0f));
			ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryActorTransform);
			
			if (GeometryActor)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				GeometryActor->SetGeometryData(Data);
				GeometryActor->FinishSpawning(GeometryActorTransform);
			}
		}

		for (const FGeometryPayload Payload: GeometryPayloads)
		{
			ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryActorClass, Payload.InitialTransform);
			if (GeometryActor)
			{
				GeometryActor->SetGeometryData(Payload.Data);
				GeometryActor->FinishSpawning(Payload.InitialTransform);
			}
		}
	}
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

