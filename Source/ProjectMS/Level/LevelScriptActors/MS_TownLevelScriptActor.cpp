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

void AMS_TownLevelScriptActor::OnPressDownEvent(FVector2D aPointerDownPosition, AActor* aPointerDownActor)
{
	if(aPointerDownActor)
	{
		if(const TObjectPtr<AMS_Actor> TargetActor = Cast<AMS_Actor>(aPointerDownActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressDownEvent();
			}
		}
	}
}

void AMS_TownLevelScriptActor::OnPressUpEvent(FVector2D aPointerUpPosition, AActor* aPointerUpActor)
{
	if(aPointerUpActor)
	{
		if(const TObjectPtr<AMS_Actor> TargetActor = Cast<AMS_Actor>(aPointerUpActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressUpEvent();
			}
		}
	}
}

