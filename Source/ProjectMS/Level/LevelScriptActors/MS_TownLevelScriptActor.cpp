// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TownLevelScriptActor.h"

#include "MS_Actor.h"
#include "Manager_Client/MS_InputManager.h"


// Sets default values
AMS_TownLevelScriptActor::AMS_TownLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_TownLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	
	gInputMng.OnPointerDownDelegate.AddDynamic(this, &AMS_TownLevelScriptActor::OnPressDownEvent);
	gInputMng.OnPointerUpDelegate.AddDynamic(this, &AMS_TownLevelScriptActor::OnPressUpEvent);
}

// Called every frame
void AMS_TownLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_TownLevelScriptActor::Destroyed()
{
	gInputMng.OnPointerDownDelegate.RemoveAll(this);
	gInputMng.OnPointerUpDelegate.RemoveAll(this);
	Super::Destroyed();
}

void AMS_TownLevelScriptActor::OnPressDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult, const FHitResult& aSpaceHitResult)
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

void AMS_TownLevelScriptActor::OnPressUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult, const FHitResult& aSpaceHitResult)
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

