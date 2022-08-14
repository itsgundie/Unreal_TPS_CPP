// TPS game made in UE4 with CPP and Blueprints

#include "UI/TPSGameHUD.h"
#include "Engine/Canvas.h"

void ATPSGameHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawCrossHair();
}

void ATPSGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    const float HalfLineSize = 13.0f;
    const float LineThickness = 2.2f;
    const FLinearColor LineColor = FLinearColor::Green;
    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
