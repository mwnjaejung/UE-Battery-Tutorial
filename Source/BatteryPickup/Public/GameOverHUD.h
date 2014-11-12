// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "GameOverHUD.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYPICKUP_API AGameOverHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	UPROPERTY()
	UFont *m_HUDFont;

	virtual void DrawHUD() override;
	
};
