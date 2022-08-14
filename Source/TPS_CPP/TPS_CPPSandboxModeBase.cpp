// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_CPPSandboxModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

ATPS_CPPSandboxModeBase::ATPS_CPPSandboxModeBase()
{
    DefaultPawnClass = ASandboxPawn::StaticClass();
    PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
