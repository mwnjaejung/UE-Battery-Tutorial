// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "BatteryPickupGameMode.generated.h"

enum class PlayState : short
{
	EPlaying,
	EGameOver,
	EUnknown,
};


UCLASS(minimalapi)
class ABatteryPickupGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	float m_DecayRate;

	PlayState GetCurrentState() const;
	void SetCurrentState(PlayState state);

	virtual void BeginPlay() override;


private:
	TArray<class ASpawnVolume*> m_SpawningVolumeActors;

	PlayState m_currentState;

	void HandleNewState(PlayState state);

};

inline PlayState ABatteryPickupGameMode::GetCurrentState() const { return m_currentState; }
