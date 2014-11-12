// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "GameOverHUD.h"
#include "BatteryPickupGameMode.h"
#include "BatteryPickupCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"


AGameOverHUD::AGameOverHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FObjectFinder<UFont> HUDFontOb(
		TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	m_HUDFont = HUDFontOb.Object;
}


void AGameOverHUD::DrawHUD()
{
	FVector2D screenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	Super::DrawHUD();

	ABatteryPickupCharacter *character = Cast<ABatteryPickupCharacter>
		(UGameplayStatics::GetPlayerPawn(this, 0));

	FString powerLevelString = FString::Printf(TEXT("%10.1f"), FMath::Abs(character->m_powerLevel));
	DrawText(powerLevelString, FColor::White, 50, 50, m_HUDFont);

	ABatteryPickupGameMode *gameMode = Cast<ABatteryPickupGameMode>(
		UGameplayStatics::GetGameMode(this));
	if (gameMode->GetCurrentState() == PlayState::EGameOver)
	{
		FVector2D gameOverSize;
		GetTextSize(TEXT("GAME OVER"), gameOverSize.X, gameOverSize.Y, m_HUDFont);

		DrawText("GAME OVER", FColor::White,
			(screenDimensions.X - gameOverSize.X) / 2.f,
			(screenDimensions.Y - gameOverSize.Y) / 2.f);
	}

}

