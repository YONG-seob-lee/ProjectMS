#include "MS_PointerData.h"

#include "MS_Define.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Widget/System/Touch/MS_TouchWidget.h"

namespace dummy
{
	float POINTER_HOLD_TERM = 0.1f;
}

FMS_PointerData::FMS_PointerData()
{
}

FMS_PointerData::~FMS_PointerData()
{
}

void FMS_PointerData::Initialize()
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	PointerHoldDelay = CommonTable->GetParameter02(CommonContents::POINTER_HOLD_DELAY);
	PointerLongTouch = CommonTable->GetParameter02(CommonContents::POINTER_LONG_TOUCH);
	PointerClickDelay = CommonTable->GetParameter02(CommonContents::POINTER_CLICK_DELAY);
}

void FMS_PointerData::Finalize()
{
	
}

void FMS_PointerData::Tick(const float aDeltaTime)
{
	if(IsPointerPressed())
	{
		ElapsedHoldTime += aDeltaTime;
		ElapsedHoldTimeInternal += aDeltaTime;
		
		if(ElapsedHoldTimeInternal >= dummy::POINTER_HOLD_TERM)
		{
			HandlePointerHold();
			ElapsedHoldTimeInternal = 0.f;
		}
		
		if(ElapsedHoldTime >= PointerLongTouch)
		{
			HandlePointerLongTouch();
		}	
	}
}

void FMS_PointerData::CalculateIntervalTime()
{
	PointerDownUpIntervalTime = (PointerUpTimestamp - PointerDownTimestamp) / IntervalTimeValue::Separation;
}

void FMS_PointerData::HandlePointerHold()
{
	MS_LOG_VERBOSITY(VeryVerbose, TEXT("ElapsedHoldTime : %f"), ElapsedHoldTime);
	
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

void FMS_PointerData::HandlePointerLongTouch() const
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

	PlayParticle();
}

void FMS_PointerData::HandlePointerGlide()
{
	if (IsPointerPressFlag == true || IsMouseRightButtonPressFlag == true)
	{
		const FVector2D PrevPointerGlidePosition = PointerGlidePosition;
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

	if(gInputMng.IsAllowGlide())
	{
		HandlePointerGlide();
	}
}

void FMS_PointerData::PlayParticle() const
{
	const TObjectPtr<UMS_TouchWidget> TouchWidget = Cast<UMS_TouchWidget>(gWidgetMng.Create_Widget_NotManaging(UMS_TouchWidget::GetWidgetPath()));
	if(TouchWidget)
	{
		TouchWidget->RebuildTouchWidget();
	}
	TouchWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	TouchWidget->AddToViewport(99999);
	TouchWidget->SetPositionInViewport(PointerDownPosition);
	TouchWidget->PlayActive();
}