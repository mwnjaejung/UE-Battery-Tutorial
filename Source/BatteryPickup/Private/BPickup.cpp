// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "BPickup.h"


ABPickup::ABPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	m_IsActive = true;

	m_baseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, "BaseSphereComponent");

	RootComponent = m_baseCollisionComponent;

	m_pickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, "PickupMesh");

	m_pickupMesh->SetSimulatePhysics(true);

	m_pickupMesh->AttachTo(RootComponent);
}


void ABPickup::OnPickedUp_Implementation()
{
	// noting
}
