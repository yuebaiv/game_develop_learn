// Fill out your copyright notice in the Description page of Project Settings.


#include "M_PlayerState.h"

void AM_PlayerState::AddPoint(int32 point)
{
	if(point > 0)
		m_PlayerPoint += point;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Add Point : %d , Current Point : %d"), point,GetPoint()));

	//调用多播委托
	PointChanged.Broadcast(GetPoint());
}
