// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_Normal.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Prop/MS_Prop.h"

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
	Super::Begin();
}

void UMS_ModeState_Normal::Exit()
{
	Super::Exit();
}

void UMS_ModeState_Normal::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aInteractableHitResult, aSpaceHitResult);
}

void UMS_ModeState_Normal::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aInteractableHitResult, aSpaceHitResult);
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

void UMS_ModeState_Normal::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Normal::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerHold(aElapsedTime, aPosition, aInteractableHitResult, aSpaceHitResult);
	
	if (aElapsedTime >= MoveToDetailModeTime)
	{
		if (AActor* InteractActor = aInteractableHitResult.GetActor())
		{
			if (InteractActor->IsA(AMS_Prop::StaticClass()))
			{
				gModeMng.ChangeState(EMS_ModeState::Construct);
			}
		}
	}
}

void UMS_ModeState_Normal::OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult, aSpaceHitResult);
}

void UMS_ModeState_Normal::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}
