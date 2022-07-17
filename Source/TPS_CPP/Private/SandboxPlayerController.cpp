// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"

#include "SandboxPawn.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandboxPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (InputComponent)
    {
        InputComponent->BindAction("SwitchPawn", IE_Pressed, this, &ASandboxPlayerController::SwitchPawn);
    }
}

void ASandboxPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::SwitchPawn()
{
    if (Pawns.Num() <= 1)
        return;
    ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
    CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
    if (!CurrentPawn)
        return;

    UE_LOG(LogSandboxPlayerController, Error, TEXT("Player's Pawn has been Changed"));
    Possess(CurrentPawn);
}
