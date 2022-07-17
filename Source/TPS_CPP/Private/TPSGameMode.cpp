// TPS game made in UE4 with CPP and Blueprints


#include "TPSGameMode.h"
#include "Player/TPSBaseCharacter.h"
#include "Player/TPSPlayerController.h"

ATPSGameMode::ATPSGameMode()
{
    DefaultPawnClass = ATPSBaseCharacter::StaticClass();
    PlayerControllerClass = ATPSPlayerController::StaticClass();
}
