#include "MS_ModeState_Construct.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MS_Define.h"
#include "Components/WidgetComponent.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_InteractionManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Prop/MS_Prop.h"
#include "Widget/Market/MS_PreviewWidget.h"


UMS_ModeState_Construct::UMS_ModeState_Construct()
{
}

void UMS_ModeState_Construct::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);
	
	gInteractionMng.OnSelectActorDelegate.AddDynamic(this, &UMS_ModeState_Construct::OnSelectProp);
	gInteractionMng.OnUnselectActorDelegate.AddDynamic(this, &UMS_ModeState_Construct::OnUnselectProp);
}

void UMS_ModeState_Construct::Finalize()
{
	Super::Finalize();

	gInteractionMng.OnUnselectActorDelegate.RemoveDynamic(this, &UMS_ModeState_Construct::OnUnselectProp);
	gInteractionMng.OnSelectActorDelegate.RemoveDynamic(this, &UMS_ModeState_Construct::OnSelectProp);
}

void UMS_ModeState_Construct::Tick(float aDeltaTime)
{
}

void UMS_ModeState_Construct::Begin()
{
	// ShowUnconstructableGrid
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		LevelScriptActor->ShowUnconstructableGrid(true);
	}

	// SelectProp
	TWeakObjectPtr<AMS_Prop> SelectedProp =  gInteractionMng.GetSelectedActor<AMS_Prop>();
	
	if (SelectedProp != nullptr)
	{
		SelectProp(SelectedProp.Get());
	}
}

void UMS_ModeState_Construct::Exit()
{
	// SelectProp
	UnselectProp();

	// ShowUnconstructableGrid
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		LevelScriptActor->ShowUnconstructableGrid(false);
	}
}

void UMS_ModeState_Construct::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aInteractableHitResult);

	AActor* InteractableActor = aInteractableHitResult.GetActor();
	
	if (IsValid(InteractableActor))
	{
		SelectProp(InteractableActor);
	}
	
	ShowPreviewWidget(false);
}

void UMS_ModeState_Construct::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aInteractableHitResult);

	ShowPreviewWidget(true);
}

void UMS_ModeState_Construct::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerMove(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerHold(aElapsedTime, aPosition, aInteractableHitResult);

	TWeakObjectPtr<AMS_Prop> SelectedProp =  gInteractionMng.GetSelectedActor<AMS_Prop>();
	
	if (SelectedProp == nullptr)
	{
		return;
	}
	
	if (SelectedProp->GetPropType() == EMS_PropType::Floor || SelectedProp->GetPropType() == EMS_PropType::Wall)
	{
		return;
	}
	
	FHitResult SpaceHitResult = {};
	if (GetHitResultUnderObjectScreenPosition(aPosition, ECollisionChannel::ECC_GameTraceChannel2, false, SpaceHitResult))
	{
		DrawDebugBox(GetWorld(), SpaceHitResult.Location, FVector(10.f), FColor::Yellow, false, 1.f);
		FVector NewObjectLocation = SpaceHitResult.Location;
		MS_LOG_Verbosity(VeryVerbose, TEXT("NewObjectLocation : %f, %f, %f"), NewObjectLocation.X, NewObjectLocation.Y, NewObjectLocation.Z);

		MovePreviewProp(NewObjectLocation);
	}
}

void UMS_ModeState_Construct::OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult);
}

void UMS_ModeState_Construct::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}

void UMS_ModeState_Construct::SelectProp(AActor* aSelectedActor)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
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
		
		// PointerPostionToObjectScreenPositionOffset
		FVector2D PointerScreenPosition = gInputMng.AcquirePointerPositionOnViewport();
		MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::PointerScreenPosition : %f, %f"), PointerScreenPosition.X, PointerScreenPosition.Y);

		FVector2D ActorCenterScreenPosition;
		GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(SelectedProp->GetActorLocation(), ActorCenterScreenPosition);
		MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::ActorCenterScreenPosition : %f, %f"), ActorCenterScreenPosition.X, ActorCenterScreenPosition.Y);
		
		PointerPostionToObjectScreenPositionOffset = ActorCenterScreenPosition - PointerScreenPosition;
		MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::ClickPositionToObjectScreenPositionOffset : %f, %f"), PointerPostionToObjectScreenPositionOffset.X, PointerPostionToObjectScreenPositionOffset.Y);
		
		if (SelectedProp->IsPreviewProp())
		{
			gInteractionMng.SelectActor(SelectedProp->GetLinkedProp());
		}
		else
		{
			gInteractionMng.SelectActor(aSelectedActor);
		}
	}
}

void UMS_ModeState_Construct::UnselectProp()
{
	gInteractionMng.UnselectActor();
}

void UMS_ModeState_Construct::OnSelectProp(AActor* aSelectedActor)	// 기존의 것과 다른 Prop이 선택되야 호출됨
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
		
		// PreviewProp
		CreatePreviewProp(SelectedProp);
	}
}

void UMS_ModeState_Construct::OnUnselectProp(AActor* aUnselectedActor)
{
	if (aUnselectedActor != nullptr)
	{
		if (AMS_Prop* UnselectedProp = Cast<AMS_Prop>(aUnselectedActor))
		{
			if (UnselectedProp->GetPropType() == EMS_PropType::Floor || UnselectedProp->GetPropType() == EMS_PropType::Wall)
			{
				return;
			}

			CancelPreviewProp(UnselectedProp);
		}
	}
}

void UMS_ModeState_Construct::OnClickApplyPreviewProp(UMS_PreviewWidget* aPreviewWidget)
{
	if (!IsValid(aPreviewWidget))
	{
		return;
	}
	
	if (aPreviewWidget != SelectedPreviewProp->GetPreviewWidget())
	{
		return;
	}

	ApplyPreviewProp();
}

void UMS_ModeState_Construct::OnClickCancelPreviewProp(UMS_PreviewWidget* aPreviewWidget)
{
}

void UMS_ModeState_Construct::CreatePreviewProp(AMS_Prop* aSelectedProp)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	if (IsValid(SelectedPreviewProp))
	{
		CancelPreviewProp(SelectedPreviewProp->GetLinkedProp().Get());
	}
	
	aSelectedProp->SetActorHiddenInGame(true);
		
	FVector Location = aSelectedProp->GetActorLocation() + FVector(0.f, 0.f, 10.f);
	FRotator Rotator = aSelectedProp->GetActorRotation();
	SelectedPreviewProp = World->SpawnActor<AMS_Prop>(aSelectedProp->GetClass(), Location, Rotator);
	SelectedPreviewProp->InitializeWhenPreviewProp(aSelectedProp);

	if (UMS_PreviewWidget* PreviewWidget = SelectedPreviewProp->GetPreviewWidget())
	{
		PreviewWidget->OnClickApplyButtonDelegate.BindUObject(this, &UMS_ModeState_Construct::OnClickApplyPreviewProp);
		PreviewWidget->OnClickCancelButtonDelegate.BindUObject(this, &UMS_ModeState_Construct::OnClickCancelPreviewProp);
	}
}

void UMS_ModeState_Construct::MovePreviewProp(const FVector& aNewLocation)
{
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		FIntVector OldCenterGridPosition =  GetGridPosition(SelectedPreviewProp->GetActorLocation(),
	SelectedPreviewProp->GetGridNum().X % 2 != 0,
	SelectedPreviewProp->GetGridNum().Y % 2 != 0);
		
		FIntVector NewCenterGridPosition = GetGridPosition(aNewLocation,
	SelectedPreviewProp->GetGridNum().X % 2 != 0,
	SelectedPreviewProp->GetGridNum().Y % 2 != 0);

		TArray<FMS_GridDataForPropSpace> NewLocationGridDatas;
		
		if (LevelScriptActor->GetGridDatasForAllPropSpaceLocations(SelectedPreviewProp, NewLocationGridDatas,
			NewCenterGridPosition - OldCenterGridPosition))
		{
			FVector NewLocationOnGrid = GetLocationOnGrid(aNewLocation,
SelectedPreviewProp->GetGridNum().X % 2 != 0,
SelectedPreviewProp->GetGridNum().Y % 2 != 0);
			
			SelectedPreviewProp->SetActorLocation(NewLocationOnGrid + FVector(0.f, 0.f, 10.f));
		}
	}
}

void UMS_ModeState_Construct::ApplyPreviewProp()
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	if (!IsValid(SelectedPreviewProp))
    {
    	return;
    }

	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		TArray<FMS_GridDataForPropSpace> NewLocationGridDatas;
		
		if (LevelScriptActor->GetGridDatasForAllPropSpaceLocations(SelectedPreviewProp, NewLocationGridDatas))
		{
			if (SelectedPreviewProp->GetLinkedProp() != nullptr)
			{
				AMS_Prop* LinkedProp = SelectedPreviewProp->GetLinkedProp().Get();
				if (LinkedProp->GetPropType() == EMS_PropType::Floor || LinkedProp->GetPropType() == EMS_PropType::Wall)
				{
					return;
				}
				
				if (CheckGridDatas(NewLocationGridDatas, LinkedProp))
				{
					// Unregister Old Datas
					TArray<FMS_GridDataForPropSpace> OldLocationGridDatas;
					LevelScriptActor->GetGridDatasForAllPropSpaceLocations(LinkedProp, OldLocationGridDatas);

					LevelScriptActor->UnregisterGridObjectData(OldLocationGridDatas);

					// Register New Datas
					LevelScriptActor->RegisterGridObjectData(NewLocationGridDatas);
					
					// Move Location
					// ToDo : Level Script로 이동
					FVector NewLocationOnGrid = GetLocationOnGrid(SelectedPreviewProp->GetActorLocation()+ FVector(0.f, 0.f, -10.f),
					SelectedPreviewProp->GetGridNum().X % 2 != 0,
					SelectedPreviewProp->GetGridNum().Y % 2 != 0);
		
					LinkedProp->SetActorLocation(NewLocationOnGrid);
				}
			}
		}
	}
}

void UMS_ModeState_Construct::CancelPreviewProp(AMS_Prop* aSelectedProp)
{
	aSelectedProp->SetActorHiddenInGame(false);
	SelectedPreviewProp->Destroy();
}

void UMS_ModeState_Construct::ShowPreviewWidget(bool bShow)
{
	if (!IsValid(SelectedPreviewProp))
	{
		return;
	}
	
	if (UWidgetComponent* PreviewWidgetComponent = SelectedPreviewProp->GetPreviewWidgetComponent())
	{
		PreviewWidgetComponent->SetVisibility(bShow);
	}
}

bool UMS_ModeState_Construct::GetHitResultUnderObjectScreenPosition(const FVector2D& aPointerPostion,
	ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return false;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return false;
	}

	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::aPointerPostion : %f, %f"), aPointerPostion.X, aPointerPostion.Y);

	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::PointerPostionToObjectScreenPositionOffset : %f, %f"), PointerPostionToObjectScreenPositionOffset.X, PointerPostionToObjectScreenPositionOffset.Y);

	FVector2D ScreenPosition = aPointerPostion + PointerPostionToObjectScreenPositionOffset;
	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::ScreenPosition : %f, %f"), ScreenPosition.X, ScreenPosition.Y);
		
	return PlayerController->GetHitResultAtScreenPosition(ScreenPosition, TraceChannel, bTraceComplex, HitResult);
}

FIntVector UMS_ModeState_Construct::GetGridPosition(const FVector& aInLocation, bool aIsXGridCenter,
	bool aIsYGridCenter, bool aIsZGridCenter) const
{
	FVector OffsetByGridCenter = FVector(
	aIsXGridCenter ? 25.f : 0.f,
	aIsYGridCenter ? 25.f : 0.f,
	aIsZGridCenter ? 25.f : 0.f);
	
	return  FIntVector(
		FMath::RoundToInt32((aInLocation.X - OffsetByGridCenter.X) / MS_GridSize.X),
		FMath::RoundToInt32((aInLocation.Y - OffsetByGridCenter.Y) / MS_GridSize.Y),
		FMath::RoundToInt32((aInLocation.Z - OffsetByGridCenter.Z) / MS_GridSize.Z));
}

FVector UMS_ModeState_Construct::GetLocationOnGrid(const FVector& aInLocation, bool aIsXGridCenter, bool aIsYGridCenter, bool aIsZGridCenter) const
{
	FVector OffsetByGridCenter = FVector(
		aIsXGridCenter ? 25.f : 0.f,
		aIsYGridCenter ? 25.f : 0.f,
		aIsZGridCenter ? 25.f : 0.f);
	
	FIntVector GridPosition = FIntVector(
		FMath::RoundToInt32((aInLocation.X - OffsetByGridCenter.X) / MS_GridSize.X),
		FMath::RoundToInt32((aInLocation.Y - OffsetByGridCenter.Y) / MS_GridSize.Y),
		FMath::RoundToInt32((aInLocation.Z - OffsetByGridCenter.Z) / MS_GridSize.Z));

	return FVector(GridPosition.X * MS_GridSize.X,
		GridPosition.Y * MS_GridSize.Y,
		GridPosition.Z * MS_GridSize.Z) + OffsetByGridCenter;
}

bool UMS_ModeState_Construct::CheckGridDatas(const TArray<const FMS_GridData*>& aGridDatas, class AMS_Prop* aTargetProp) const
{
	for (const FMS_GridData* GridData : aGridDatas)
	{
		if (IsValid(aTargetProp) && GridData->Object == aTargetProp)
		{
			continue;
		}
		
		if (GridData->Object != nullptr)
		{
			return false;
		}
	}

	return true;
}

bool UMS_ModeState_Construct::CheckGridDatas(const TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces,
	AMS_Prop* aTargetProp) const
{
	for (const FMS_GridDataForPropSpace& GridDataForPropSpace : aGridDatasForPropSpaces)
	{
		TArray<const FMS_GridData*> GridDatas = GridDataForPropSpace.GridDatas;
		
		for (const FMS_GridData* GridData : GridDatas)
		{
			if (IsValid(aTargetProp) && GridData->Object == aTargetProp)
			{
				continue;
			}
		
			if (GridData->Object != nullptr)
			{
				return false;
			}
		}
	}

	return true;
}
