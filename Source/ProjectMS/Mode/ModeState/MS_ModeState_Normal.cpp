// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_Normal.h"

#include "Components/CanvasPanelSlot.h"
#include "Manager_Client/MS_InteractionManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Prop/MS_Prop.h"
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
	Super::Begin();
}

void UMS_ModeState_Normal::Exit()
{
	Super::Exit();
}

void UMS_ModeState_Normal::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aInteractableHitResult);
}

void UMS_ModeState_Normal::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aInteractableHitResult);
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

	if (AActor* InteractActor = aInteractableHitResult.GetActor())
	{
		if (InteractActor->IsA(AMS_Prop::StaticClass()))
		{
			gInteractionMng.SelectActor(InteractActor);
				
			gModeMng.ChangeState(EMS_ModeState::Construct);
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

	if (const TObjectPtr<AActor> InteractActor = aInteractableHitResult.GetActor())
	{
		if (InteractActor->IsA(AMS_Prop::StaticClass()))
		{
			if(const TObjectPtr<AMS_Prop> PropActor = Cast<AMS_Prop>(InteractActor))
			{
				// const TObjectPtr<UMS_StorageCacheTable> StorageTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
				// MS_CHECK(StorageTable);
				//
				// const FMS_StorageData* StorageData = StorageTable->GetStorageData(PropActor->GetTableIndex());
				// if(StorageData == nullptr)
				// {
				// 	return;
				// }
				// if(StorageData->StorageType == static_cast<int32>(EMS_StorageType::Display))
				// {
				// 	
				// }
				// else if(StorageData->StorageType == static_cast<int32>(EMS_StorageType::Shelf))
				// {
				// 	
				// }
				// else if(StorageData->StorageType == static_cast<int32>(EMS_StorageType::Pallet))
				// {
				// 	
				// }
				
				PropActor->GetUnitHandleId();

				gWidgetMng.SetCustomPositionWidget(gWidgetMng.Create_Widget(UMS_StorageStatusWidget::GetWidgetName(), false), aPosition);
			}
		}
	}
}

void UMS_ModeState_Normal::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}
