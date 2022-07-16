// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

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
	SpawnGeometryActors();
}

void AGeometryHubActor::SpawnGeometryActors()
{
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
				GeometryActor->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				GeometryActor->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				GeometryActor->FinishSpawning(GeometryActorTransform);
			}
		}
		for (const FGeometryPayload Payload: GeometryPayloads)
		{
			ABaseGeometryActor* GeometryActor = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryActorClass, Payload.InitialTransform);
			if (GeometryActor)
			{
				GeometryActor->SetGeometryData(Payload.Data);
				GeometryActor->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				GeometryActor->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
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

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor's Name %s and Color %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if (!Actor) return;
	UE_LOG(LogGeometryHub, Error, TEXT("Timer finished for actor %s"), *Actor->GetName());

	ABaseGeometryActor* GeometryActor = Cast<ABaseGeometryActor>(Actor);
	if (!GeometryActor) return;
	UE_LOG(LogGeometryHub, Display, TEXT("Upcast is succeded, Actor's final color is %s"), *GeometryActor->GetGeometryData().Color.ToString());
	GeometryActor->SetLifeSpan(3.3f);
}

