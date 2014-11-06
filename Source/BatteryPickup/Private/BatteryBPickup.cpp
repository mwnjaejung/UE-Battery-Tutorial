// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "BatteryBPickup.h"


ABatteryBPickup::ABatteryBPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	m_powerLevel = 150.f;

}


void ABatteryBPickup::OnPickedUp_Implementation()
{
	Super::OnPickedUp_Implementation();

	Destroy();	
}
