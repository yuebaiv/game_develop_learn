// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CrossHairWidget.h"
#include "GameFramework/PlayerController.h"
#include "AndroidProjectPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class ANDROIDPROJECT_API AAndroidProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;



	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCrossHairWidget* CrossHairWidget;
};
