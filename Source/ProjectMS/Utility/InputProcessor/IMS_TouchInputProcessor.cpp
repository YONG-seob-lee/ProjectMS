// Fill out your copyright notice in the Description page of Project Settings.


#include "IMS_TouchInputProcessor.h"

#include "MS_Define.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeState/MS_ModeStateBase.h"

void IMS_TouchInputProcessor::Initialize()
{
}

void IMS_TouchInputProcessor::Finalize()
{
	for(const auto& PointerData : PointerDatas)
	{
		PointerData.Value->Finalize();
		delete PointerData.Value;
	}
	
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
	TargetPointerData->SetPointerUpPosition(gInputMng.AcquirePointerPositionOnViewport());

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