// Copyright Epic Games, Inc. All Rights Reserved.

#include "AndroidProjectGameMode.h"
#include "AndroidProjectCharacter.h"
#include "GoalMesh.h"
#include "M_PlayerState.h"
#include "ToolBuilderUtil.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

AAndroidProjectGameMode::AAndroidProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	PlayerStateClass = AM_PlayerState::StaticClass();

}

void AAndroidProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	//生成重要立方体
	GenImportantCube();
	//倒计时开始
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AAndroidProjectGameMode::UpdateCountdown, 0.1f, true);
}

void AAndroidProjectGameMode::GenImportantCube() const
{
	TArray<AActor*> Cube;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AGoalMesh::StaticClass(),Cube);
	int CubeNum = Cube.Num();
	TSet<int32> RandomNumbersSet;
	
	// 生成唯一的随机数并将它们添加到 Set 中
	if(CubeNum > 0 && CubeNum >= ImportantCubeNum)
	{
		while (RandomNumbersSet.Num() < ImportantCubeNum)
		{
			int32 RandomNumber = FMath::RandRange(0, CubeNum-1);  // 生成指定范围内的随机数
			RandomNumbersSet.Add(RandomNumber);  // 添加到 Set 中，如果重复则不会被添加
		}

		// 输出生成的唯一随机数
		for (int32 RandomNumber : RandomNumbersSet)
		{
			Cast<AGoalMesh>(Cube[RandomNumber])->ChangeToImportant();
		}
	}


}

void AAndroidProjectGameMode::GetPlayerPoints()
{
	// 获取当前游戏的世界
	UWorld* World = GetWorld();
	if (World)
	{
		// 遍历所有 PlayerController
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			if (PlayerController)
			{
				// 打印玩家控制器的名字
				UE_LOG(LogTemp, Warning, TEXT("Player Controller: %s"), *PlayerController->GetName());
				int32 Playerpoint = PlayerController->GetPlayerState<AM_PlayerState>()->GetPoint();
				UE_LOG(LogTemp, Warning, TEXT("Player Point: %d"), Playerpoint);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Your Points are : %d"), Playerpoint));
			}
		}
	}
}

void AAndroidProjectGameMode::UpdateCountdown()
{
	// 每秒减少倒计时时间
	TimeToCountDown-= 0.1f;

	// 当倒计时结束时
	if (TimeToCountDown <= 0)
	{
		// 停止定时器
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);

		// 打印信息到控制台
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Time Out!!!"));
			UE_LOG(LogTemp, Warning, TEXT("Time Out!!!"));
			GetPlayerPoints();
			
		}
	}
}

float AAndroidProjectGameMode::GetRemainTime()
{
	return FMath::Max(TimeToCountDown,0.0);
}
