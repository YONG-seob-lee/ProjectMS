// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InteractionManager.h"


UMS_InteractionManager::UMS_InteractionManager()
{
	InteractionManager = this;
}

UMS_InteractionManager* UMS_InteractionManager::GetInstance()
{
	return InteractionManager;
}

void UMS_InteractionManager::SelectActor(TWeakObjectPtr<AActor> aSelectedActor)
{
	if (SelectedActor == aSelectedActor)
	{
		return;
	}
	
	UnselectActor();

	if (aSelectedActor != nullptr)
	{
		SelectedActor = aSelectedActor;
		OnSelectActorDelegate.Broadcast(SelectedActor.Get());
	}
}

void UMS_InteractionManager::UnselectActor()
{
	if (SelectedActor != nullptr)
	{
		// Broadcast 중 재호출 되지 않도록 안전코드 개념으로 null 처리 먼저 함
		AActor* TargetActor = SelectedActor.Get();
		SelectedActor = nullptr;
		
		OnUnselectActorDelegate.Broadcast(TargetActor);
	}
}
