// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "SpawnVolume.h"
#include "BPickup.h"


ASpawnVolume::ASpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
	, m_isSpawningEnable(true)
{
	m_WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, "WhereToSpawn");

	RootComponent = m_WhereToSpawn;

	m_spawnDelayRangeLow = 1.f;
	m_spawnDelayRangeHigh = 4.5f;
	m_SpawnDelay = GetRandomSpawnDelay();

	m_SpawnTime = 0;
	PrimaryActorTick.bCanEverTick = true;
}



void ASpawnVolume::SpawnPickup()
{
	if (m_WhereToSpawn != NULL)
	{
		UWorld * const world = GetWorld();
		if (world)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			FVector spawnLocation = GetRandomPointInVolume();

			FRotator spawnRotation;
			spawnRotation.Yaw = FMath::FRand() * 360.f;
			spawnRotation.Pitch = FMath::FRand() * 360.f;
			spawnRotation.Roll = FMath::FRand() * 360.f;

			AActor * const spawnedPickup = world->SpawnActor<AActor>(m_WhatToSpawn, spawnLocation, spawnRotation, spawnParams);
		}
	}
}


float ASpawnVolume::GetRandomSpawnDelay()
{
	return FMath::FRandRange(m_spawnDelayRangeLow, m_spawnDelayRangeHigh);
}


FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector location;

	FVector origin = m_WhereToSpawn->Bounds.Origin;
	FVector boxExtent = m_WhereToSpawn->Bounds.BoxExtent;

	float minX = origin.X - boxExtent.X / 2.f;
	float minY = origin.Y - boxExtent.Y / 2.f;
	float minZ = origin.Z - boxExtent.Z / 2.f;

	float maxX = origin.X + boxExtent.X / 2.f;
	float maxY = origin.Y + boxExtent.Y / 2.f;
	float maxZ = origin.Z + boxExtent.Z / 2.f;

	location.X = FMath::FRandRange(minX, maxX);
	location.Y = FMath::FRandRange(minY, maxY);
	location.Z = FMath::FRandRange(minZ, maxZ);

	return location;
}


void ASpawnVolume::Tick(float DeltaSeconds)
{
	if (m_isSpawningEnable)
	{
		m_SpawnTime += DeltaSeconds;

		bool bShouldSpawn = (m_SpawnTime > m_SpawnDelay);

		if (bShouldSpawn)
		{
			SpawnPickup();

			m_SpawnTime -= m_SpawnDelay;

			m_SpawnDelay = GetRandomSpawnDelay();
		}
	}
}


void ASpawnVolume::EnableSpawning()
{
	m_isSpawningEnable = true;
}


void  ASpawnVolume::DisableSpawning()
{
	m_isSpawningEnable = false;
}
