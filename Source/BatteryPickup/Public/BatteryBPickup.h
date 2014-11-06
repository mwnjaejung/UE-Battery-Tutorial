// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BPickup.h"
#include "BatteryBPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYPICKUP_API ABatteryBPickup : public ABPickup
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Power)
	float m_powerLevel;

	void OnPickedUp_Implementation() override;
	
};
