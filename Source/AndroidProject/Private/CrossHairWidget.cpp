// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"


void UCrossHairWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}

void UCrossHairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UCrossHairWidget::PlayShootAnimation()
{
	if(CrossHairMove)
	{
		PlayAnimation(CrossHairMove);
	}
}

void UCrossHairWidget::PlayHitAnimation()
{
	if(CrossHairHit)
	{
		PlayAnimation(CrossHairHit);
	}
}
