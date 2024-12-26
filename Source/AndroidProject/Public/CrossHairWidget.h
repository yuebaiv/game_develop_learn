// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "CrossHairWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANDROIDPROJECT_API UCrossHairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UImage* CrosshairR;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UImage* CrosshairL;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UImage* CrosshairU;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UImage* CrosshairD;

	UPROPERTY(BlueprintReadOnly,Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* CrossHairMove;

	UPROPERTY(BlueprintReadOnly,Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* CrossHairHit;

	UFUNCTION()
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PlayShootAnimation();

	UFUNCTION(BlueprintCallable)
	void PlayHitAnimation();
	
};
