// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYPICKUP_API ABPickup : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Pickup)
	bool m_IsActive;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<USphereComponent> m_baseCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<UStaticMeshComponent> m_pickupMesh;

	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();


};
