// Fill out your copyright notice in the Description page of Project Settings.


#include "IMS_TouchInputProcessor.h"

#include "MS_Define.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Slate/SceneViewport.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/System/Touch/MS_TouchWidget.h"

FMS_PointerData::FMS_PointerData()
{
}

FMS_PointerData::~FMS_PointerData()
{
	MS_DeleteObject(TouchWidget);
}

void FMS_PointerData::Initialize()
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	PointerHoldDelay = CommonTable->GetParameter02(CommonContents::POINTER_HOLD_DELAY);
	PointerLongTouch = CommonTable->GetParameter02(CommonContents::POINTER_LONG_TOUCH);
	PointerClickDelay = CommonTable->GetParameter02(CommonContents::POINTER_CLICK_DELAY);
	
	TouchWidget = Cast<UMS_TouchWidget>(gWidgetMng.Create_Widget_NotManaging(UMS_TouchWidget::GetWidgetPath()));
	if(TouchWidget)
	{
		TouchWidget->RebuildTouchWidget();
	}

	TouchWidget->SetOnFinishedParticleRendererFunc([this]()
	{
		if(OnFinishParticleCallback)
		{
			OnFinishParticleCallback();
		}
	});
}

void FMS_PointerData::Finalize()
{
	
}

void FMS_PointerData::Tick(const float aDeltaTime)
{
	ElapsedHoldTime += aDeltaTime;

	if(ElapsedHoldTime >= PointerLongTouch)
	{
		HandlePointerLongTouch();
	}
}

void FMS_PointerData::CalculateIntervalTime()
{
	PointerDownUpIntervalTime = (PointerUpTimestamp - PointerDownTimestamp) / IntervalTimeValue::Separation;
}

void FMS_PointerData::HandlePointerHold()
{
	MS_LOG_Verbosity(Warning, TEXT("ElapsedHoldTime : %f"), ElapsedHoldTime);
	
	PointerHoldPosition = gInputMng.AcquirePointerPositionOnViewport();

	FHitResult InteractableHitResult = {};
	gInputMng.GetHitResultUnderPointerPosition(ECollisionChannel::ECC_GameTraceChannel1, false, InteractableHitResult);
	
	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
	if (IsValid(CurrentModeState))
	{
		CurrentModeState->OnInputPointerHold(ElapsedHoldTime, PointerHoldPosition, InteractableHitResult);
	}
	
	gInputMng.OnPointerHoldDelegate.Broadcast(ElapsedHoldTime, PointerHoldPosition, InteractableHitResult);
}

void FMS_PointerData::HandlePointerLongTouch()
{
	FHitResult InteractableHitResult = {};
	gInputMng.GetHitResultUnderPointerPosition(ECollisionChannel::ECC_GameTraceChannel1, false, InteractableHitResult);
	
	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
	if(IsValid(CurrentModeState))
	{
		CurrentModeState->OnInputPointerLongTouch(ElapsedHoldTime, PointerHoldPosition, InteractableHitResult);
	}

	gInputMng.OnPointerLongTouchDelegate.Broadcast(ElapsedHoldTime, PointerHoldPosition, InteractableHitResult);
}

void FMS_PointerData::HandlePointerClick()
{
	if (PointerDownUpIntervalTime < PointerClickDelay)
	{
		PointerClickIntervalTime = (FDateTime::UtcNow().GetTicks() - PointerClickTimestamp) / IntervalTimeValue::Separation;
		PointerClickTimestamp = FDateTime::UtcNow().GetTicks();
		PointerClickPosition = gInputMng.AcquirePointerPositionOnViewport();
		
		FHitResult InteractableHitResult = {};
		gInputMng.GetHitResultUnderPointerPosition(ECollisionChannel::ECC_GameTraceChannel1, false, InteractableHitResult);
		
		UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
		if (IsValid(CurrentModeState))
		{
			CurrentModeState->OnInputPointerClick(PointerClickPosition, InteractableHitResult);
		}
		
		gInputMng.OnPointerClickDelegate.Broadcast(PointerClickPosition, InteractableHitResult);
	}
}

void FMS_PointerData::HandlePointerGlide()
{
	if (IsPointerPressFlag == true || IsMouseRightButtonPressFlag == true)
	{
		FVector2D PrevPointerGlidePosition = PointerGlidePosition;
		PointerGlidePosition = PointerMovePosition;
		if(PrevPointerGlidePosition.Equals(PointerParameter::DefaultVector))
		{
			PointerGlidePositionDelta = FVector2D::ZeroVector;
		}
		else
		{
			PointerGlidePositionDelta = PointerGlidePosition - PrevPointerGlidePosition;
		}

		PointerGlidePositionDeltaArray.Add(PointerGlidePositionDelta);
		if (PointerGlidePositionDeltaArray.Num() > PointerParameter::MoveDeltaArrayMax)
		{
			PointerGlidePositionDeltaArray.RemoveAt(PointerParameter::ArrayFirst, EAllowShrinking::Yes);
		}

		PointerGlidePositionDeltaTrend = FVector2D::ZeroVector;
		for (int i = 0; i < PointerGlidePositionDeltaArray.Num(); ++i)
		{
			PointerGlidePositionDeltaTrend += PointerGlidePositionDeltaArray[i];
		}
		PointerGlidePositionDeltaTrend /= PointerMovePositionDeltaArray.Num();

		if (IsPointerPressFlag == true)
		{
			UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
			if (IsValid(CurrentModeState))
			{
				CurrentModeState->OnInputPointerGlide(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
			}
			
			gInputMng.OnPointerGlideDelegate.Broadcast(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
		}

		if (IsMouseRightButtonPressFlag == true)
		{
			UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
			if (IsValid(CurrentModeState))
			{
				CurrentModeState->OnMouseRightButtonGlide(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
			}
			
			gInputMng.OnMouseRightButtonGlideDelegate.Broadcast(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
		}
	}
	else
	{
		PointerGlidePosition = PointerParameter::DefaultVector;
		PointerGlidePositionDelta = PointerParameter::DefaultVector;
		PointerGlidePositionDeltaArray.Empty();
		PointerGlidePositionDeltaTrend = PointerParameter::DefaultVector;
	}
}

void FMS_PointerData::HandlePinchAction()
{
}

void FMS_PointerData::UpdatePointerMovePosition()
{
	const FVector2D PrevPointerMovePosition = PointerMovePosition;
	PointerMovePosition = gInputMng.AcquirePointerPositionOnViewport();

	if(PrevPointerMovePosition.Equals(PointerParameter::DefaultVector))
	{
		PointerMovePositionDelta = FVector2D::ZeroVector;
	}
	else
	{
		PointerMovePositionDelta = PointerMovePosition - PrevPointerMovePosition;
	}

	PointerMovePositionDeltaArray.Add(PointerMovePositionDelta);
	if(PointerMovePositionDeltaArray.Num() > PointerParameter::MoveDeltaArrayMax)
	{
		PointerMovePositionDeltaArray.RemoveAt(PointerParameter::ArrayFirst, EAllowShrinking::Yes);	
	}
	
	PointerMovePositionDeltaTrend = FVector2D::ZeroVector;
	for(int32 i = 0 ; i <PointerMovePositionDeltaArray.Num(); i++)
	{
		PointerMovePositionDeltaTrend += PointerMovePositionDeltaArray[i];
	}
	PointerMovePositionDeltaTrend /= PointerMovePositionDeltaArray.Num();

	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
	if (IsValid(CurrentModeState))
	{
		CurrentModeState->OnInputPointerMove(PointerMovePosition, PointerMovePositionDelta, PointerMovePositionDeltaTrend);
	}

	gInputMng.OnPointerMoveDelegate.Broadcast(PointerMovePosition, PointerMovePositionDelta, PointerMovePositionDeltaTrend);
	
	HandlePointerGlide();
}

void FMS_PointerData::PlayParticle() const
{
	if(!TouchWidget)
	{
		return;
	}
	
	TouchWidget->AddToViewport(99999);
	TouchWidget->SetPositionInViewport(PointerDownPosition);
	TouchWidget->PlayActive();
}

void IMS_TouchInputProcessor::Initialize()
{
}

void IMS_TouchInputProcessor::Finalize()
{
	PointerDatas.Empty();
}

void IMS_TouchInputProcessor::AddReferencedObjects(FReferenceCollector& aCollector)
{
}

FString IMS_TouchInputProcessor::GetReferencerName() const
{
	return TEXT("TouchInputProcessor");
}

void IMS_TouchInputProcessor::Tick(const float aDeltaTime, FSlateApplication& aSlateApp, TSharedRef<ICursor> aCursor)
{
	for(const auto& PointerData : PointerDatas)
	{
		if(PointerData.Value)
		{
			PointerData.Value->Tick(aDeltaTime);
		}
	}
}

bool IMS_TouchInputProcessor::HandleMouseButtonDownEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	MS_LOG(TEXT("IMS_TouchInputProcessor::HandleMouseButtonDownEvent    PointerIndex : %d"), aMouseEvent.GetPointerIndex());

	FMS_PointerData* NewPointerData = CreatePointer(aMouseEvent);
	NewPointerData->Initialize();
	
	ShootLineTrace(NewPointerData->GetPointerDownPosition());
	
	FingerCount++;

	return false;
}

bool IMS_TouchInputProcessor::HandleMouseMoveEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	if(FingerCount == 2)
	{
		
	}

	FMS_PointerData* TargetPointerData = GetPointerData(aMouseEvent.GetPointerIndex());
	if(!TargetPointerData)
	{
		return false;
	}
	
	TargetPointerData->UpdatePointerMovePosition();

	return IInputProcessor::HandleMouseMoveEvent(aSlateApp, aMouseEvent);
}

bool IMS_TouchInputProcessor::HandleMouseButtonUpEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	MS_LOG(TEXT("IMS_TouchInputProcessor::HandleMouseButtonUpEvent    PointerIndex : %d"), aMouseEvent.GetPointerIndex());
	FMS_PointerData* TargetPointerData = GetPointerData(aMouseEvent.GetPointerIndex());
	if(!TargetPointerData)
	{
		return false;
	}
	
	TargetPointerData->SetPointerPressFlag(false);
	TargetPointerData->SetPointerUpTimestamp(FDateTime::UtcNow().GetTicks());
	TargetPointerData->SetPointerUpPosition(AcquirePointerPositionOnViewport());

	FHitResult InteractableHitResult = {};
	gInputMng.GetHitResultUnderPointerPosition(ECollisionChannel::ECC_GameTraceChannel1, false, InteractableHitResult);
	
	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
	if (IsValid(CurrentModeState))
	{
		CurrentModeState->OnInputPointerUpEvent(TargetPointerData->GetPointerUpPosition(), InteractableHitResult);
	}

	gInputMng.OnPointerUpDelegate.Broadcast(TargetPointerData->GetPointerUpPosition(), InteractableHitResult);

	TargetPointerData->ResetElapsedHoldTime();
	TargetPointerData->CalculateIntervalTime();

	TargetPointerData->HandlePointerClick();
	TargetPointerData->PlayParticle();
	
	FingerCount--;

	return IInputProcessor::HandleMouseButtonUpEvent(aSlateApp, aMouseEvent);
}

bool IMS_TouchInputProcessor::HandleMouseButtonDoubleClickEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{	
	return IInputProcessor::HandleMouseButtonDoubleClickEvent(aSlateApp, aMouseEvent);
}

FMS_PointerData* IMS_TouchInputProcessor::CreatePointer(const FPointerEvent& aMouseEvent)
{
	FMS_PointerData* PointerData = new FMS_PointerData();
	
	PointerDatas.Emplace(aMouseEvent.GetPointerIndex(), PointerData);
	PointerData->SetOnFinishParticleFunc([this, PointerData]()
	{
		PointerDatas.Remove(PointerData->GetPointerIndex());
		PointerData->Finalize();
		delete PointerData;
	});
	
	PointerData->SetPointerIndex(aMouseEvent.GetPointerIndex());
	PointerData->SetPointerPressFlag(true);
	PointerData->SetPointerDownTimestamp(FDateTime::UtcNow().GetTicks());
	PointerData->SetPointerDownPosition(gInputMng.AcquirePointerPositionOnViewport());

	return PointerData;
}

FMS_PointerData* IMS_TouchInputProcessor::GetPointerData(uint32 aPointerIndex)
{
	for(const auto& PointerData : PointerDatas)
	{
		if(PointerData.Value->IsPointerPressed() == false)
		{
			continue;
		}
		
		if(PointerData.Key == aPointerIndex)
		{
			return PointerData.Value;
		}
	}

	return nullptr;
}

FVector2D IMS_TouchInputProcessor::AcquirePointerPositionOnViewport() const
{
	FVector2D PointerPosition = {};
	
#if PLATFORM_WINDOWS || PLATFORM_MAC
	//const TObjectPtr<UWorld> World = GetWorld();
	//MS_CHECK(World);

	//const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	//MS_CHECK(PlayerController);
	
	//PlayerController->GetMousePosition(PointerPosition.X, PointerPosition.Y);
	
#elif PLATFORM_ANDROID || PLATFORM_IOS
	bool CurrentlyTouchPressFlag = {};
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, PointerPosition.X, PointerPosition.Y, CurrentlyTouchPressFlag);
#endif
	return PointerPosition;
}

void IMS_TouchInputProcessor::ShootLineTrace(const FVector2D& aPointerDownPosition)
{
	FHitResult InteractableHitResult;
	
	gInputMng.GetHitResultUnderPointerPosition(ECollisionChannel::ECC_GameTraceChannel1, false, InteractableHitResult);

	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
	if (IsValid(CurrentModeState))
	{
		CurrentModeState->OnInputPointerDownEvent(aPointerDownPosition, InteractableHitResult);
	}

	gInputMng.OnPointerDownDelegate.Broadcast(aPointerDownPosition, InteractableHitResult);
}