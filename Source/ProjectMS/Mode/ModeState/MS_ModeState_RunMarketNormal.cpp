// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_RunMarketNormal.h"

#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "Manager_Client/MS_InteractionManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Prop/MS_Prop.h"
#include "Widget/Market/Modal/MS_MarketEndModal.h"


UMS_ModeState_RunMarketNormal::UMS_ModeState_RunMarketNormal()
{
}

void UMS_ModeState_RunMarketNormal::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);

	ScheduleEvent.Emplace(0, static_cast<int32>(EMS_MarketScheduleEvent::Prepare));
	ScheduleEvent.Emplace(20, static_cast<int32>(EMS_MarketScheduleEvent::LoadingUnloading));
	ScheduleEvent.Emplace(140, static_cast<int32>(EMS_MarketScheduleEvent::OpenMarket));
	ScheduleEvent.Emplace(770, static_cast<int32>(EMS_MarketScheduleEvent::Deadline));
	ScheduleEvent.Emplace(800, static_cast<int32>(EMS_MarketScheduleEvent::CloseMarket));
}

void UMS_ModeState_RunMarketNormal::Finalize()
{
	Super::Finalize();
}

void UMS_ModeState_RunMarketNormal::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ModeState_RunMarketNormal::Begin()
{
	Super::Begin();

	// Select
	gInteractionMng.OnSelectActorDelegate.AddDynamic(this, &UMS_ModeState_RunMarketNormal::OnSelectActor);
	gInteractionMng.OnUnselectActorDelegate.AddDynamic(this, &UMS_ModeState_RunMarketNormal::OnUnselectActor);
	
	TWeakObjectPtr<AActor> SelectedActor =  gInteractionMng.GetSelectedActor();
	
	if (SelectedActor != nullptr)
	{
		UnselectActor();
	}
}

void UMS_ModeState_RunMarketNormal::Exit()
{
	TWeakObjectPtr<AActor> SelectedActor =  gInteractionMng.GetSelectedActor();
	
	if (SelectedActor != nullptr)
	{
		UnselectActor();
	}
	
	// Delegate
	gInteractionMng.OnUnselectActorDelegate.RemoveDynamic(this, &UMS_ModeState_RunMarketNormal::OnUnselectActor);
	gInteractionMng.OnSelectActorDelegate.RemoveDynamic(this, &UMS_ModeState_RunMarketNormal::OnSelectActor);
	
	Super::Exit();
}

void UMS_ModeState_RunMarketNormal::UpdateMinute(int32 aCurrentMinute)
{
	Super::UpdateMinute(aCurrentMinute);
}

void UMS_ModeState_RunMarketNormal::UpdateScheduleEvent(int32 aScheduleEvent)
{
	Super::UpdateScheduleEvent(aScheduleEvent);

	EMS_MarketScheduleEvent MarketNormalScheduleEvent = static_cast<EMS_MarketScheduleEvent>(aScheduleEvent);
	
	switch(MarketNormalScheduleEvent)
	{
	case EMS_MarketScheduleEvent::Prepare:
		{
			gWidgetMng.ShowToastMessage(TEXT("준비 단계! 출근 시간은 7:00까지 입니다."));
			break;
		}
	case EMS_MarketScheduleEvent::LoadingUnloading:
		{
			gWidgetMng.ShowToastMessage(TEXT("상하차가 시작되었습니다!"));
			break;
		}
	case EMS_MarketScheduleEvent::OpenMarket:
		{
			gWidgetMng.ShowToastMessage(TEXT("매장 오픈~!! 달려보자고!"));
			break;
		}
	case EMS_MarketScheduleEvent::Deadline:
		{
			gWidgetMng.ShowToastMessage(TEXT("곧 마켓 영업이 끝납니다. 계산하고 나가주세요~!"));
			break;
		}
	case EMS_MarketScheduleEvent::CloseMarket:
		{
			gWidgetMng.ShowToastMessage(TEXT("매장 문 닫겠습니다~!"));
			FMS_ModalParameter ModalParameter;
			ModalParameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketEndModal::GetWidgetPath());
			gWidgetMng.ShowModalWidget(ModalParameter);
			break;
		}
	default:
		{
			break;
		}
	}
}

void UMS_ModeState_RunMarketNormal::OnInputPointerDownEvent(FVector2D aPointerDownPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarketNormal::OnInputPointerUpEvent(FVector2D aPointerUpPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarketNormal::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerMove(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_RunMarketNormal::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_RunMarketNormal::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_RunMarketNormal::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerHold(aElapsedTime, aPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarketNormal::OnInputPointerLongTouch(float aElapsedTime, const FVector2D& aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerLongTouch(aElapsedTime, aPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarketNormal::OnInputPointerClick(const FVector2D& aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult);

	AActor* InteractableActor = aInteractableHitResult.GetActor();
	
	if (IsValid(InteractableActor) && InteractableActor->IsA(AMS_Prop::StaticClass()))
	{
		SelectActor(InteractableActor);
	}
}

void UMS_ModeState_RunMarketNormal::OnInputPointerDoubleClickEvent(FVector2D aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDoubleClickEvent(aPosition, aInteractableHitResult);

	if (const TObjectPtr<AActor> InteractActor = aInteractableHitResult.GetActor())
	{
		if(const TObjectPtr<AMS_Prop> PropActor = Cast<AMS_Prop>(InteractActor))
		{
			SelectActor(InteractActor);
			
			PropActor->OpenStatusWidget(aPosition);
		}
	}
}

void UMS_ModeState_RunMarketNormal::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}

void UMS_ModeState_RunMarketNormal::SelectActor(AActor* aSelectedActor)
{
	if (!IsValid(aSelectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aSelectedActor))
	{
		if (SelectedProp->GetPropType() == EMS_PropType::Floor || SelectedProp->GetPropType() == EMS_PropType::Wall)
		{
			return;
		}
		
		gInteractionMng.SelectActor(aSelectedActor);
	}
}

void UMS_ModeState_RunMarketNormal::UnselectActor()
{
	gInteractionMng.UnselectActor();
}

void UMS_ModeState_RunMarketNormal::OnSelectActor(AActor* aSelectedActor)
{
	if (!IsValid(aSelectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aSelectedActor))
	{
		SelectedProp->OnSelectProp(EMS_ModeState::RunMarketNormal);
	}
}

void UMS_ModeState_RunMarketNormal::OnUnselectActor(AActor* aUnselectedActor)
{
	if (!IsValid(aUnselectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aUnselectedActor))
	{
		SelectedProp->OnUnselectProp(EMS_ModeState::RunMarketNormal);
	}
}
