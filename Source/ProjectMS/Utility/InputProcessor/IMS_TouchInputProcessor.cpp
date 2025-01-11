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
	FMS_PointerData* NewPointerData = CreatePointer(aMouseEvent);
	NewPointerData->Initialize();
	
	ShootLineTrace(NewPointerData->GetPointerDownPosition());

	NewPointerData->PlayParticle();
	
	FingerCount++;

	return false;
}

bool IMS_TouchInputProcessor::HandleMouseMoveEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	if(FingerCount == 2)
	{
		HandleRotate();
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
	
	DestroyPointer(TargetPointerData);
	FingerCount--;

	return IInputProcessor::HandleMouseButtonUpEvent(aSlateApp, aMouseEvent);
}

bool IMS_TouchInputProcessor::HandleMouseButtonDoubleClickEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	FingerCount++; // 손가락 카운트 오류 방지용.
	
	return IInputProcessor::HandleMouseButtonDoubleClickEvent(aSlateApp, aMouseEvent);
}

void IMS_TouchInputProcessor::HandleRotate()
{
	const FMS_PointerData* FirstFinger = nullptr;
	const FMS_PointerData* SecondFinger = nullptr;
	
	for(const auto& PointerData : PointerDatas)
	{
		if(PointerData.Value->IsPointerPressed())
		{
			if(FirstFinger == nullptr)
			{
				FirstFinger = PointerData.Value;
			}
			else
			{
				SecondFinger = PointerData.Value;
			}
		}
	}

	//FVector2D Pivot = FirstFinger->GetPointerDownPosition() - SecondFinger->GetPointerDownPosition();
}

FMS_PointerData* IMS_TouchInputProcessor::CreatePointer(const FPointerEvent& aMouseEvent)
{
	FMS_PointerData* PointerData = new FMS_PointerData();
	
	PointerDatas.Emplace(aMouseEvent.GetPointerIndex(), PointerData);
	
	PointerData->SetPointerIndex(aMouseEvent.GetPointerIndex());
	PointerData->SetPointerPressFlag(true);
	PointerData->SetPointerDownTimestamp(FDateTime::UtcNow().GetTicks());
	PointerData->SetPointerDownPosition(gInputMng.AcquirePointerPositionOnViewport());

	return PointerData;
}

void IMS_TouchInputProcessor::DestroyPointer(FMS_PointerData* aPointerData)
{
	FMS_PointerData** TargetPointerData = PointerDatas.Find(aPointerData->GetPointerIndex());
	if(!TargetPointerData)
	{
		return;
	}

	if((*TargetPointerData)->IsPointerPressed())
	{
		return;
	}
	PointerDatas.Remove(aPointerData->GetPointerIndex());
	aPointerData->Finalize();
	delete aPointerData;
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