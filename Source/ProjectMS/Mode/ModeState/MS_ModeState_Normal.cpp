﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_Normal.h"

#include "Manager_Client/MS_InteractionManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Prop/MS_Prop.h"
#include "Widget/MS_Widget.h"
#include "Widget/Market/Storage/MS_StorageStatusWidget.h"


UMS_ModeState_Normal::UMS_ModeState_Normal()
{
}

void UMS_ModeState_Normal::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);
}

void UMS_ModeState_Normal::Finalize()
{
	Super::Finalize();
}

void UMS_ModeState_Normal::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ModeState_Normal::Begin()
{
	// Item Manager
	gItemMng.UpdateNotPlacedItemsToPalletItems();
	
	// Delegate
	gInteractionMng.OnSelectActorDelegate.AddDynamic(this, &UMS_ModeState_Normal::OnSelectActor);
	gInteractionMng.OnUnselectActorDelegate.AddDynamic(this, &UMS_ModeState_Normal::OnUnselectActor);

	// SelectProp
	TWeakObjectPtr<AMS_Prop> SelectedProp =  gInteractionMng.GetSelectedActor<AMS_Prop>();
	
	if (SelectedProp != nullptr)
	{
		OnSelectActor(SelectedProp.Get());
	}
}

void UMS_ModeState_Normal::Exit()
{
	UnselectActor();
	
	// Delegate
	gInteractionMng.OnUnselectActorDelegate.RemoveDynamic(this, &UMS_ModeState_Normal::OnUnselectActor);
	gInteractionMng.OnSelectActorDelegate.RemoveDynamic(this, &UMS_ModeState_Normal::OnSelectActor);
}

void UMS_ModeState_Normal::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& InteractableHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, InteractableHitResult);
	
	if(InteractableHitResult.IsValidBlockingHit())
	{
		CachePressDownLocation = aPointerDownPosition;
	}
}

void UMS_ModeState_Normal::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& InteractableHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, InteractableHitResult);

	CachePressDownLocation = FVector2D::ZeroVector;
}

void UMS_ModeState_Normal::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerMove(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Normal::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Normal::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Normal::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerHold(aElapsedTime, aPosition, aInteractableHitResult);
}

void UMS_ModeState_Normal::OnInputPointerLongTouch(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerLongTouch(aElapsedTime, aPosition, aInteractableHitResult);

	if (const TObjectPtr<AActor> InteractActor = aInteractableHitResult.GetActor())
	{
		if(FVector2D::Distance(CachePressDownLocation, aPosition) > 10.f)
		{
			return;
		}

		//if (gInteractionMng.GetSelectedActor() != nullptr)
		//{
		//	return;
		//}
		
		if(InteractActor.IsA(AMS_Prop::StaticClass()))
		{
			SelectActor(InteractActor);
		}
	}
}

void UMS_ModeState_Normal::OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult);
}

void UMS_ModeState_Normal::OnInputPointerDoubleClickEvent(FVector2D aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDoubleClickEvent(aPosition, aInteractableHitResult);
}

void UMS_ModeState_Normal::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}

void UMS_ModeState_Normal::SelectActor(AActor* aSelectedActor)
{
	if (!IsValid(aSelectedActor))
	{
		return;
	}
	
	if (aSelectedActor->IsA(AMS_Prop::StaticClass()))
	{
		gInteractionMng.SelectActor(aSelectedActor);
	}
}

void UMS_ModeState_Normal::UnselectActor()
{
	gInteractionMng.UnselectActor();
}

void UMS_ModeState_Normal::OnSelectActor(AActor* aSelectedActor)
{
	if (!IsValid(aSelectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aSelectedActor))
	{
		SelectedProp->OnSelectProp(EMS_ModeState::Normal);
		
		SelectedProp->CancelSelectedDelegate.BindWeakLambda(this,
			[this](TWeakObjectPtr<AMS_Prop> aTargetProp)
			{
				if (aTargetProp != nullptr)
				{
					if (gInteractionMng.GetSelectedActor() == aTargetProp)
					{
						UnselectActor();
					}
				}
			});
	}
}

void UMS_ModeState_Normal::OnUnselectActor(AActor* aUnselectedActor)
{
	if (!IsValid(aUnselectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aUnselectedActor))
	{
		SelectedProp->OnUnselectProp(EMS_ModeState::Normal);
	}
}