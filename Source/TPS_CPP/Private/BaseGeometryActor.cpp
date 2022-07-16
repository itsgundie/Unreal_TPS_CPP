// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	FTransform Transform = GetActorTransform();
	InitLocation = GetActorLocation();
	SetColor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRateSec, true);
	
	// PrintTransform();
	// printTypes();
	// printStringTypes();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor %s destroyed"), *GetName());
	Super::EndPlay(EndPlayReason);
}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Weapons num: %d, kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health count: %f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Is Aluve: %d"), isAlive);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Is Loaded: %d"), static_cast<int>(isLoaded));
}

void ABaseGeometryActor::PrintStringTypes()
{
	FString Name = "John Wayne";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name is %s"), *Name);


	UE_LOG(LogTemp, Display, TEXT("WAT U DOIN' HERE?"));
	UE_LOG(LogTemp, Warning, TEXT("WAT U DOIN' HERE?"));
	UE_LOG(LogTemp, Error, TEXT("WAT U DOIN' HERE?"));

	FString WeaponsNumString = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString isAliveStr = "Is Alive - " + FString(isAlive ? "true" : "false");
	FString Stat = FString::Printf(TEXT("\nAll Stats:\n %s \n %s \n %s"), *WeaponsNumString, *HealthStr, *isAliveStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, Name);
		GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Green, Stat, true, FVector2D(1.75f, 1.75f));
	}
}

void ABaseGeometryActor::PrintTransform()
{
	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's Name: %s"), *GetName());
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's Transform: %s"), *Transform.ToString())
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's Location: %s"), *Location.ToString())
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's Rotation: %s"), *Rotation.ToString())
	UE_LOG(LogBaseGeometry, Warning, TEXT("Actor's Scale: %s"), *Scale.ToString())
	UE_LOG(LogBaseGeometry, Error, TEXT("Readable Transform: %s"), *Transform.ToHumanReadableString());
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
		{
			FVector CurrentLocation = GetActorLocation();
			if (GetWorld())
			{
				float Time = GetWorld()->GetTimeSeconds();
				CurrentLocation.Z = InitLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
				SetActorLocation(CurrentLocation);
			}
		}
	case EMovementType::Static: break;
	default: break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
{
	if (!BaseMesh) return;
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		UE_LOG(LogBaseGeometry, Display, TEXT("TimerCount: %i, MaxTimerCount: %i, New Generated Color is: %s"),
			TimerCount, MaxTimerCount,  *NewColor.ToString());
		SetColor(NewColor);
		OnColorChanged.Broadcast(NewColor, GetName());
	}
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped!"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMovement();
}
