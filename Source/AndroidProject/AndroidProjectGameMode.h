// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AndroidProjectGameMode.generated.h"

UCLASS(minimalapi)
class AAndroidProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAndroidProjectGameMode();

	virtual void BeginPlay() override;

	void GenImportantCube() const;

	void GetPlayerPoints();
	
	FTimerHandle CountdownTimerHandle;  // 用于管理定时器

	UPROPERTY(EditAnywhere)
	int32 ImportantCubeNum = 3;

	UPROPERTY(EditAnywhere)
	float TimeToCountDown = 10.0f;

	UFUNCTION()
	void UpdateCountdown();

	float GetRemainTime();
};



