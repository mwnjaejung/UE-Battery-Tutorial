// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYPICKUP_API ASpawnVolume : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleInstanceOnly, Category=Spawning)
	TSubobjectPtr<UBoxComponent> m_WhereToSpawn;

	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	TSubclassOf<class ABPickup> m_WhatToSpawn;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Spawning)
	float m_spawnDelayRangeLow;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Spawning)
	float m_spawnDelayRangeHigh;

	UFUNCTION(BlueprintPure, Category = Spawning)
	FVector GetRandomPointInVolume();


private:
	float GetRandomSpawnDelay();
	float m_SpawnDelay;
	void SpawnPickup();

};
