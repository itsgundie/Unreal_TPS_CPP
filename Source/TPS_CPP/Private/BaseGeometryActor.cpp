// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

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
	FVector Location = Transform.GetLocation();
	FRotator Rotatation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	InitLocation = GetActorLocation();
	PrintTransform();
	// printTypes();
	// printStringTypes();
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

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 8, FColor::Green, Stat, true, FVector2D(1.75f, 1.75f));
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
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
			SetActorLocation(CurrentLocation);
		}
	case EMovementType::Static: break;
	default: break;
	}
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleMovement();
}
