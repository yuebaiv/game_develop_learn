// Fill out your copyright notice in the Description page of Project Settings.


#include "M_HUDWidget.h"

#include "M_PlayerState.h"



void UM_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if(TextBlock_Point && PlayerController)
	{
		AM_PlayerState* PlayerState = PlayerController->GetPlayerState<AM_PlayerState>();
		PlayerState->PointChanged.AddUObject(this, &UM_HUDWidget::UpdateHUDPoint);
		
	}
}

void UM_HUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// 获取当前的 GameMode
	AAndroidProjectGameMode* GameMode = Cast<AAndroidProjectGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode && TextBlock_Time)
	{
		// 获取剩余时间并更新 TextBlock
		float RemainingTime = GameMode->GetRemainTime();
		TextBlock_Time->SetText(FText::AsNumber(RemainingTime));
	}
}

void UM_HUDWidget::UpdateHUDPoint(int32 Point)
{
	TextBlock_Point->SetText(FText::AsNumber(Point));
}
