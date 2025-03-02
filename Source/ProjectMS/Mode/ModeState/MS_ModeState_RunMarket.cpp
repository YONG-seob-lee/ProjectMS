// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_RunMarket.h"

#include "Character/MS_CharacterBase.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "Manager_Client/MS_InteractionManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeObject/Supervisor/Staff/MS_StaffSupervisor.h"
#include "Prop/MS_Prop.h"
#include "Widget/Market/Modal/MS_MarketEndModal.h"
#include "Widget/Market/Storage/MS_StorageStatusWidget.h"


UMS_ModeState_RunMarket::UMS_ModeState_RunMarket()
{
}

void UMS_ModeState_RunMarket::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);

	ScheduleEvent.Emplace(00, static_cast<int32>(EMS_MarketScheduleEvent::Prepare));
	ScheduleEvent.Emplace(20, static_cast<int32>(EMS_MarketScheduleEvent::TruckIn));
	ScheduleEvent.Emplace(40, static_cast<int32>(EMS_MarketScheduleEvent::LoadingUnloading));
	ScheduleEvent.Emplace(100, static_cast<int32>(EMS_MarketScheduleEvent::CustomerStart));
	ScheduleEvent.Emplace(160, static_cast<int32>(EMS_MarketScheduleEvent::OpenMarket));
	ScheduleEvent.Emplace(790, static_cast<int32>(EMS_MarketScheduleEvent::Deadline));
	ScheduleEvent.Emplace(ScheduleDefault::GamePlayMinute, static_cast<int32>(EMS_MarketScheduleEvent::CloseMarket));
}

void UMS_ModeState_RunMarket::Finalize()
{
	Super::Finalize();
}

void UMS_ModeState_RunMarket::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_ModeState_RunMarket::Begin()
{
	Super::Begin();

	// Select
	gInteractionMng.OnSelectActorDelegate.AddDynamic(this, &UMS_ModeState_RunMarket::OnSelectActor);
	gInteractionMng.OnUnselectActorDelegate.AddDynamic(this, &UMS_ModeState_RunMarket::OnUnselectActor);
	
	TWeakObjectPtr<AActor> SelectedActor =  gInteractionMng.GetSelectedActor();
	
	if (SelectedActor != nullptr)
	{
		UnselectActor();
	}
}

void UMS_ModeState_RunMarket::Exit()
{
	TWeakObjectPtr<AActor> SelectedActor =  gInteractionMng.GetSelectedActor();
	
	if (SelectedActor != nullptr)
	{
		UnselectActor();
	}
	
	// Delegate
	gInteractionMng.OnUnselectActorDelegate.RemoveDynamic(this, &UMS_ModeState_RunMarket::OnUnselectActor);
	gInteractionMng.OnSelectActorDelegate.RemoveDynamic(this, &UMS_ModeState_RunMarket::OnSelectActor);
	
	Super::Exit();
}

void UMS_ModeState_RunMarket::UpdateMinute(int32 aCurrentMinute)
{
	Super::UpdateMinute(aCurrentMinute);
}

void UMS_ModeState_RunMarket::UpdateScheduleEvent(int32 aScheduleEvent)
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
			gScheduleMng.UpdateDailySheet();
			gScheduleMng.WriteDiary();
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

void UMS_ModeState_RunMarket::OnInputPointerDownEvent(FVector2D aPointerDownPosition, AActor* aHitActor)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aHitActor);

	if (aHitActor)
	{
		CachePressDownActor = aHitActor;
	}
}

void UMS_ModeState_RunMarket::OnInputPointerUpEvent(FVector2D aPointerUpPosition, AActor* aHitActor)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aHitActor);

	CachePressDownActor = nullptr;
	
	if(gSequenceMng.IsPlayingSequence())
	{
		gSequenceMng.StopSequence();
	}
}

void UMS_ModeState_RunMarket::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerMove(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_RunMarket::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_RunMarket::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_RunMarket::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerHold(aElapsedTime, aPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarket::OnInputPointerLongTouch(float aElapsedTime, const FVector2D& aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerLongTouch(aElapsedTime, aPosition, aInteractableHitResult);
	
	if (const TObjectPtr<AActor> InteractActor = aInteractableHitResult.GetActor())
	{
		if (CachePressDownActor != nullptr && InteractActor != CachePressDownActor)
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

void UMS_ModeState_RunMarket::OnInputPointerClick(const FVector2D& aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarket::OnInputPointerDoubleClickEvent(FVector2D aPosition,
	const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDoubleClickEvent(aPosition, aInteractableHitResult);
}

void UMS_ModeState_RunMarket::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}

void UMS_ModeState_RunMarket::SelectActor(AActor* aSelectedActor)
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

void UMS_ModeState_RunMarket::UnselectActor()
{
	gInteractionMng.UnselectActor();
}

void UMS_ModeState_RunMarket::OnSelectActor(AActor* aSelectedActor)
{
	if (!IsValid(aSelectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aSelectedActor))
	{
		SelectedProp->OnSelectProp(EMS_ModeState::RunMarket);
	}

	OpenStatusWidget(aSelectedActor);
}

void UMS_ModeState_RunMarket::OnUnselectActor(AActor* aUnselectedActor)
{
	if (!IsValid(aUnselectedActor))
	{
		return;
	}
	
	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aUnselectedActor))
	{
		SelectedProp->OnUnselectProp(EMS_ModeState::RunMarket);
	}

	CloseStatusWidget();
}

void UMS_ModeState_RunMarket::OpenStatusWidget(AActor* aSelectedActor)
{
	if(const TObjectPtr<AMS_Prop> PropActor = Cast<AMS_Prop>(aSelectedActor))
	{
		StatusWidget = PropActor->OpenStatusWidget();

		if (StatusWidget != nullptr)
		{
			if (UMS_StorageStatusWidget* StorageStatusWidget = Cast<UMS_StorageStatusWidget>(StatusWidget))
			{
				StorageStatusWidget->OnClickedConfirmButtonDelegate.BindUObject(this, &UMS_ModeState_RunMarket::UnselectActor);
			}
		}
	}
}

void UMS_ModeState_RunMarket::CloseStatusWidget()
{
	if (StatusWidget != nullptr)
	{
		gWidgetMng.DestroyWidget(StatusWidget.Get());
	}
}

void UMS_ModeState_RunMarket::RegisterLevelSpecificActorToSupervisor(const FName& aName, TWeakObjectPtr<AActor> aActor) const
{
	if (aName == LevelSpecificActorName::UglyDuck)
	{
		if (StaffSupervisor)
		{
			TWeakObjectPtr<AMS_CharacterBase> UglyDuckCharacter = Cast<AMS_CharacterBase>(aActor);
			if (UglyDuckCharacter != nullptr)
			{
				StaffSupervisor->RegisterPreSpawnedCharacter(1, UglyDuckCharacter);
			}
		}
	}
}
