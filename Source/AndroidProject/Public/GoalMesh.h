// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalMesh.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
UCLASS()
class ANDROIDPROJECT_API AGoalMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGoalMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* m_GoalMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Components")
	UBoxComponent* m_BoxCollision;

	void ChangeToImportant();

	UPROPERTY(EditAnywhere)
	int32 Point = 1;
	UPROPERTY(EditAnywhere)
	float ScaleFactor = 0.2;
	UPROPERTY(EditAnywhere)
	int32 HitCountBeforeDestory = 2;
	UPROPERTY(VisibleAnywhere)
	bool isImportant = false;
	
	
	
	
};
