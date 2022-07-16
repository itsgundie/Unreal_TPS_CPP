// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPS_CPPGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

ATPS_CPPGameModeBase::ATPS_CPPGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
