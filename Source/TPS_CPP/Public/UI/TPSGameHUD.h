// TPS game made in UE4 with CPP and Blueprints

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TPSGameHUD.generated.h"

UCLASS()
class TPS_CPP_API ATPSGameHUD : public AHUD
{
	GENERATED_BODY()
public:
    virtual void DrawHUD() override;

private:
    void DrawCrossHair();
};
