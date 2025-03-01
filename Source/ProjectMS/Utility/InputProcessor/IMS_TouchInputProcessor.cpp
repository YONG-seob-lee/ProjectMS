// Fill out your copyright notice in the Description page of Project Settings.


#include "IMS_TouchInputProcessor.h"

#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Slate/SceneViewport.h"

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

	const FGeometry CachedGeometry = GEngine->GameViewport->GetGameViewport()->GetCachedGeometry();
	const FVector2D AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(aMouseEvent.GetScreenSpacePosition());
	ShootLineTrace(AbsoluteScreenPosition, EMS_TouchActionType::Down);
	FingerCount++;

	return false;
}

bool IMS_TouchInputProcessor::HandleMouseMoveEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	if(FingerCount == 2)
	{
		HandleZoomIn();
	}

	FMS_PointerData* TargetPointerData = GetPointerData(aMouseEvent.GetPointerIndex());
	if(!TargetPointerData)
	{
		return false;
	}

	const FGeometry CachedGeometry = GEngine->GameViewport->GetGameViewport()->GetCachedGeometry();
	const FVector2D AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(aMouseEvent.GetScreenSpacePosition());
	TargetPointerData->UpdatePointerMovePosition(AbsoluteScreenPosition);

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

	const FGeometry CachedGeometry = GEngine->GameViewport->GetGameViewport()->GetCachedGeometry();
	const FVector2d AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(aMouseEvent.GetScreenSpacePosition());
	TargetPointerData->SetPointerUpPosition(AbsoluteScreenPosition);

	ShootLineTrace(TargetPointerData->GetPointerUpPosition(), EMS_TouchActionType::Up);

	TargetPointerData->ResetElapsedHoldTime();
	TargetPointerData->CalculateIntervalTime();
	TargetPointerData->HandlePointerClick(AbsoluteScreenPosition);
	TargetPointerData->PlayParticle();
	
	DestroyPointer(TargetPointerData);
	FingerCount--;

	return IInputProcessor::HandleMouseButtonUpEvent(aSlateApp, aMouseEvent);
}

bool IMS_TouchInputProcessor::HandleMouseButtonDoubleClickEvent(FSlateApplication& aSlateApp, const FPointerEvent& aMouseEvent)
{
	FingerCount++; // 손가락 카운트 오류 방지용.
	const FGeometry CachedGeometry = GEngine->GameViewport->GetGameViewport()->GetCachedGeometry();
	const FVector2d AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(aMouseEvent.GetScreenSpacePosition());
	ShootLineTrace(AbsoluteScreenPosition, EMS_TouchActionType::Double);
	
	return IInputProcessor::HandleMouseButtonDoubleClickEvent(aSlateApp, aMouseEvent);
}

bool IMS_TouchInputProcessor::HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp,
	const FPointerEvent& InWheelEvent, const FPointerEvent* InGestureEvent)
{
	return IInputProcessor::HandleMouseWheelOrGestureEvent(SlateApp, InWheelEvent, InGestureEvent);
}

void IMS_TouchInputProcessor::HandleZoomIn()
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
	if(FirstFinger == nullptr || SecondFinger == nullptr)
	{
		return;
	}

	const float NewDistance = FVector2D::Distance(FirstFinger->GetPointerMovePosition(), SecondFinger->GetPointerMovePosition());
	if(TwoFingersDistance > NewDistance)
	{
		gCameraMng.ZoomCamera(-1.f);
	}
	else if(TwoFingersDistance < NewDistance)
	{
		gCameraMng.ZoomCamera(1.f);
	}

	TwoFingersDistance = NewDistance;
}

bool IMS_TouchInputProcessor::IsPointerPressed() const
{
	for(const auto& PointerData : PointerDatas)
	{
		if(PointerData.Value->IsPointerPressed())
		{
			return true;
		}
	}

	return false;
}

FMS_PointerData* IMS_TouchInputProcessor::CreatePointer(const FPointerEvent& aMouseEvent)
{
	FMS_PointerData* PointerData = new FMS_PointerData();
	
	PointerDatas.Emplace(aMouseEvent.GetPointerIndex(), PointerData);
	
	PointerData->SetPointerIndex(aMouseEvent.GetPointerIndex());
	PointerData->SetPointerPressFlag(true);
	PointerData->SetPointerDownTimestamp(FDateTime::UtcNow().GetTicks());

	const FGeometry CachedGeometry = GEngine->GameViewport->GetGameViewport()->GetCachedGeometry();
	const FVector2d AbsoluteScreenPosition = CachedGeometry.AbsoluteToLocal(aMouseEvent.GetScreenSpacePosition());
	PointerData->SetPointerDownPosition(AbsoluteScreenPosition);

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

void IMS_TouchInputProcessor::ShootLineTrace(const FVector2D& aPointerDownPosition, EMS_TouchActionType aType)
{
	if(gInputMng.IsAllowInteractActor() == false)
	{
		return;
	}
	
	FHitResult InteractableHitResult;
	
	gInputMng.GetHitResultUnderPointerPosition(aPointerDownPosition, ECollisionChannel::ECC_GameTraceChannel1, false, InteractableHitResult);

	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();

	AActor* HitActor = InteractableHitResult.GetActor();

	if(!HitActor)
	{
		return;
	}
	
	if(aType == EMS_TouchActionType::Down)
	{
		if (IsValid(CurrentModeState))
		{
			CurrentModeState->OnInputPointerDownEvent(aPointerDownPosition, HitActor);
		}
		gInputMng.OnPointerDownDelegate.Broadcast(aPointerDownPosition, InteractableHitResult);
	}
	else if(aType == EMS_TouchActionType::Up)
	{
		if (IsValid(CurrentModeState))
		{
			CurrentModeState->OnInputPointerUpEvent(aPointerDownPosition, HitActor);
		}
		
		gInputMng.OnPointerUpDelegate.Broadcast(aPointerDownPosition, InteractableHitResult);
	}
	else if(aType == EMS_TouchActionType::Double)
	{
		if (IsValid(CurrentModeState))
		{
			CurrentModeState->OnInputPointerDoubleClickEvent(aPointerDownPosition, InteractableHitResult);
		}
	}
}
