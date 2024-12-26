// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalMesh.h"

#include "MovieSceneSequenceID.h"
#include "M_PlayerState.h"
#include "Components/BoxComponent.h"


// Sets default values
AGoalMesh::AGoalMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = m_BoxCollision;
	m_GoalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PointMesh"));
	m_GoalMesh->SetupAttachment(m_BoxCollision);
	m_GoalMesh->SetGenerateOverlapEvents(false);
	m_GoalMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_BoxCollision->SetGenerateOverlapEvents(true);
	m_BoxCollision->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void AGoalMesh::BeginPlay()
{
	Super::BeginPlay();

	m_BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AGoalMesh::OnOverlapBegin);
	m_BoxCollision->OnComponentHit.AddDynamic(this, &AGoalMesh::OnHit);
	
}

// Called every frame
void AGoalMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGoalMesh::ChangeToImportant()
{
	isImportant = true;
	UMaterialInterface* MeshMaterial = m_GoalMesh->GetMaterial(0);
	UMaterialInstanceDynamic* DynamicMaterial = m_GoalMesh->CreateDynamicMaterialInstance(0,MeshMaterial,NAME_None);
	if (MeshMaterial && isImportant)
	{
		// 设置材质的颜色参数（假设颜色参数名称为 "Color"）
		DynamicMaterial->SetVectorParameterValue(FName("Base Color"), FVector(1.0,0,0));  // 设置为红色
	}
}

void AGoalMesh::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                               bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this)&& OtherActor->ActorHasTag("Projectile"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped with %s"), *OtherActor->GetName());
		FString YourString = TEXT("Overlapped!!");
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, YourString);
	}
}

void AGoalMesh::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this)&& OtherActor->ActorHasTag("Projectile"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit by %s"), *OtherActor->GetName());
		FString YourString = TEXT("Hit!!");
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, YourString);

		//缩放和销毁
		FVector Scale = GetActorScale3D();
		if((Scale - ScaleFactor).X <= 0)
			Destroy();
		SetActorScale3D(Scale - ScaleFactor);
		if((--HitCountBeforeDestory) == 0)
		{
			Destroy();
		}
		//计算积分
		APlayerController* controller = Cast<APlayerController>(OtherActor->GetOwner()->GetOwner());
		if(controller)
		{
			AM_PlayerState* m_PlayerState = controller->GetPlayerState<AM_PlayerState>();
			m_PlayerState->AddPoint(isImportant? 2 * Point : Point);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("controller is : %s"), *controller->GetName()));
		}
		
	}
}




