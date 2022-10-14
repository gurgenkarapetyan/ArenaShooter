// Arena Shooter


#include "UI/GameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"


void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* const PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->AddToViewport();
	}
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();

	// DrawCrossHair();
}

void AGameHUD::DrawCrossHair()
{
	const TInterval<float> Center( Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	constexpr float HalfLineSize = 10.f;
	constexpr float LineThickness = 2.f;
	const FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
