// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "BatteryPickup.h"
#include "BatteryPickupGameMode.h"
#include "BatteryPickupCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "spawnvolume.h"
#include "GameOverHUD.h"


ABatteryPickupGameMode::ABatteryPickupGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	HUDClass = AGameOverHUD::StaticClass();

	m_DecayRate = 0.25f;

}


void ABatteryPickupGameMode::Tick(float DeltaSeconds)
{
	ABatteryPickupCharacter *myCharacter = Cast<ABatteryPickupCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (myCharacter->m_powerLevel > 0.5f)
	{
		myCharacter->m_powerLevel = FMath::FInterpTo(myCharacter->m_powerLevel,
			0, DeltaSeconds, m_DecayRate );

	}
	else
	{
		SetCurrentState(PlayState::EGameOver);
	}

}


void ABatteryPickupGameMode::SetCurrentState(PlayState state)
{
	m_currentState = state;

	HandleNewState(state);

}


void ABatteryPickupGameMode::HandleNewState(PlayState state)
{
	switch (state)
	{
	case PlayState::EPlaying:
	{
								for (auto volume : m_SpawningVolumeActors)
								{
									volume->EnableSpawning();
								}
	}
	break;

	case PlayState::EGameOver:

	{
								 for (auto volume : m_SpawningVolumeActors)
								 {
									 volume->DisableSpawning();
								 }

								 APlayerController *playerController =
									 UGameplayStatics::GetPlayerController(this, 0);
								 playerController->SetCinematicMode(true, true, true);
	}
		break;

	case PlayState::EUnknown:
		break;
	default:
		break;
	}
}


void ABatteryPickupGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		ASpawnVolume::StaticClass(), foundActors);		

	for (auto actor : foundActors)
	{
		ASpawnVolume *volume = Cast<ASpawnVolume>(actor);
		if (volume)
		{
			m_SpawningVolumeActors.Add(volume);
		}
	}

	SetCurrentState(PlayState::EPlaying);
}
