// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AndroidProject/AndroidProjectGameMode.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "M_HUDWidget.generated.h"


/**
 * 
 */
UCLASS()
class ANDROIDPROJECT_API UM_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UTextBlock* TextBlock_Time;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UTextBlock* TextBlock_Point;

	UFUNCTION()
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateHUDPoint(int32 Point);
	
	
};
