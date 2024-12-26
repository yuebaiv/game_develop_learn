// Copyright Epic Games, Inc. All Rights Reserved.


#include "AndroidProjectPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "M_PlayerState.h"
#include "Engine/LocalPlayer.h"

void AAndroidProjectPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	AM_PlayerState* m_PlayerState = Cast<AM_PlayerState>(PlayerState);
}
