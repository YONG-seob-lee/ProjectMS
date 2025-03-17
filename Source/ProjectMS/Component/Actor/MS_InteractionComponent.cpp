// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InteractionComponent.h"

#include "MS_ActorBase.h"
#include "MS_Define.h"


UMS_InteractionComponent::UMS_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMS_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_InteractionComponent::PostLoad()
{
	Super::PostLoad();

	Actor = Cast<AActor>(GetOuter());
}

void UMS_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMS_InteractionComponent::OnPressedEvent()
{
	MS_CHECK(TEXT("================== UMS_InteractionComponent::OnPressedEvent"));
	if(DefaultScale.X < 0.f)
	{
		DefaultScale = Actor->GetActorScale3D();
	}
	
	if(Actor.IsValid())
	{
		Actor->SetActorRelativeScale3D(DefaultScale * 0.9f);
	}
	
	//GetWorld()->GetTimerManager().SetTimer(OnPressedFinishedHandle, this, &UMS_InteractionComponent::OnReleasedEvent, 0.5f, false);
}

void UMS_InteractionComponent::OnReleasedEvent()
{
	MS_CHECK(TEXT("================== UMS_InteractionComponent::OnReleasedEvent"));
	
	if(Actor.IsValid())
	{
		Actor->SetActorRelativeScale3D(DefaultScale * 1.1f);
	}

	GetWorld()->GetTimerManager().SetTimer(OnReleasedFinishedHandle, this, &UMS_InteractionComponent::SetOnReleasedFinished, 0.5f, false);

	if(const TObjectPtr<AMS_ActorBase> MSActor = Cast<AMS_ActorBase>(Actor))
	{
		MSActor->LaunchEvent();
	}
}

void UMS_InteractionComponent::SetOnReleasedFinished()
{
	Actor->SetActorRelativeScale3D(DefaultScale);
}

