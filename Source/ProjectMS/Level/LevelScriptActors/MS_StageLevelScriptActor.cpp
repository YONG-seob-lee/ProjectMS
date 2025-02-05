// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StageLevelScriptActor.h"

#include "MS_Actor.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"


// Sets default values
AMS_StageLevelScriptActor::AMS_StageLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_StageLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	gInputMng.OnPointerDownDelegate.AddDynamic(this, &AMS_StageLevelScriptActor::OnPressDownEvent);
	gInputMng.OnPointerUpDelegate.AddDynamic(this, &AMS_StageLevelScriptActor::OnPressUpEvent);

	gCameraMng.LocateAndRotateCamera(FVector(12600.f, -6380.f, 3200.f), FRotator(0.f, -90.f, 0.f), EMS_ViewCameraType::QuarterView);
	gCameraMng.LocateAndRotateCamera(FVector(13310.f, -8000.f, 390.f), FRotator(45.f, -90.f, 0.f), EMS_ViewCameraType::SideView);
}

// Called every frame
void AMS_StageLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_StageLevelScriptActor::Destroyed()
{
	gInputMng.OnPointerDownDelegate.RemoveAll(this);
	gInputMng.OnPointerUpDelegate.RemoveAll(this);
	Super::Destroyed();
	Super::Destroyed();
}

void AMS_StageLevelScriptActor::OnPressDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
	AActor* PointerDownActor = aInteractableHitResult.GetActor();
	if(IsValid(PointerDownActor))
	{
		if(const TObjectPtr<AMS_Actor> TargetActor = Cast<AMS_Actor>(PointerDownActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressDownEvent();
			}
		}
	}
}

void AMS_StageLevelScriptActor::OnPressUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult)
{
	AActor* PointerUpActor = aInteractableHitResult.GetActor();
	if(IsValid(PointerUpActor))
	{
		if(const TObjectPtr<AMS_Actor> TargetActor = Cast<AMS_Actor>(PointerUpActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressUpEvent();
			}
		}
	}
}

