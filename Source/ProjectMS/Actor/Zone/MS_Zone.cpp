// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Zone.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MS_Define.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Controller/MS_PlayerController.h"
#include "PlayerState/MS_PlayerState.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_HISMManager.h"
#include "Prop/MS_Prop.h"
#include "Prop/Gate/MS_Gate.h"
#include "Units/MS_GateUnit.h"
#include "Widget/Market/MS_ZoneOpenWidget.h"


AMS_Zone::AMS_Zone(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer), ZoneIndex(INDEX_NONE), ZoneType(EMS_ZoneType::None)
{
	// Component
	ZoneBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneBoxComponent"));
	if (ZoneBoxComponent)
	{
		ZoneBoxComponent->SetupAttachment(SceneRootComponent);
	}

	ZoneOpenMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZoneOpenMeshComponent"));
	if (ZoneOpenMeshComponent)
	{
		ZoneOpenMeshComponent->SetupAttachment(ZoneBoxComponent);

		ZoneOpenMeshComponent->SetVisibility(false);
	}

	ZoneOpenWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ZoneOpendWidgetComponent"));
	if (ZoneOpenWidgetComponent)
	{
		ZoneOpenWidgetComponent->SetupAttachment(ZoneBoxComponent);

		ZoneOpenWidgetComponent->SetVisibility(false);
	}
	
	LocationToWallDatas.Empty();
}

void AMS_Zone::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_Zone::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeZoneData();
	
	RegisterDefalutAttachedProps();
}

void AMS_Zone::BeginPlay()
{
	Super::BeginPlay();

	if (ZoneOpenWidgetComponent)
	{
		if (UMS_ZoneOpenWidget* ZoneOpenWidget = Cast<UMS_ZoneOpenWidget>(ZoneOpenWidgetComponent->GetWidget()))
		{
			ZoneOpenWidget->OnClickZoneOpenButtonDelegate.BindUObject(this, &AMS_Zone::OnClickZoneOpenWidget);
			ZoneOpenWidget->SetPrice(ZonePrice);
		}
	}
	
	if (ZoneType == EMS_ZoneType::Pallet || ZoneType == EMS_ZoneType::Outside)
	{
		SetZoneOpened(true);	// LevelScriptActor에서 확인해서 OnZoneOpened 호출
	}
}

void AMS_Zone::InitializeZoneData()
{
	MS_CHECK(ZoneBoxComponent);
	
	ZoneLocation = ZoneBoxComponent->GetComponentLocation() - ZoneBoxComponent->GetUnscaledBoxExtent();
	
	ZoneSize = ZoneBoxComponent->GetUnscaledBoxExtent() * 2.f;
	
	ZoneGridNum = FIntVector2(FMath::RoundToInt32(ZoneSize.X / MS_GridSize.X),
		FMath::RoundToInt32(ZoneSize.Y / MS_GridSize.Y));
	
	ZoneWorldGridPosition = FMS_GridData::ConvertLocationToGridPosition(ZoneLocation);

	CreateGrids();
}

void AMS_Zone::CreateGrids()
{
	Grids.Empty();

	for (int i = 0; i < ZoneGridNum.Y; ++i)
	{
		for (int j = 0; j < ZoneGridNum.X; ++j)
		{
			FIntVector2 GridPosition = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + FIntVector2(j, i);
			
			Grids.Emplace(GridPosition, FMS_GridData(this, GridPosition));
		}
	}
}

void AMS_Zone::RegisterDefalutAttachedProps()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (AActor* AttachedActor : AttachedActors)
	{
		if (AMS_Gate* Gate = Cast<AMS_Gate>(AttachedActor))
		{
			Gate->SetZoneData(this);

			// Create Unit
			TObjectPtr<UMS_GateUnit> GateUnit = Cast<UMS_GateUnit>(gUnitMng.CreateUnit(EMS_UnitType::Gate, Gate->GetTableIndex(), false));
			if (IsValid(GateUnit))
			{
				// Set Unit Actor
				if (!GateUnit->SetUnitActor(Gate))
				{
					MS_ERROR(TEXT("[%s] Set Unit Actor Fail"), *MS_FUNC_STRING);
					MS_ENSURE(false);
				}
				else
				{
					GateUnit->GetActor()->SetActorHiddenInGame(true);
					
					GateUnits.Emplace(GateUnit);
				}
			}
			else
			{
				MS_ERROR(TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
				MS_ENSURE(false);
			}

			// Prop Space
			const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = Gate->GetPropSpaceComponents();

			for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
			{
				FIntVector2 StartGridPosition = FIntVector2::ZeroValue;
				FIntVector2 GridNum = FIntVector2::ZeroValue;
			
				PropSpaceComponent->GetGridPositions(StartGridPosition, GridNum);
			
				// Set With Grid
				for (int i = 0; i < GridNum.Y; ++i)
				{
					for (int j = 0; j < GridNum.X; ++j)
					{
						FIntVector2 GridPosition = FIntVector2(StartGridPosition.X + j, StartGridPosition.Y + i);
						
						if (IsGridContained(GridPosition))
						{
							RegisterObjectToGrid(GridPosition, PropSpaceComponent);
						}
						else
						{
							MS_ERROR(TEXT("[%s] All gate prop spaces must be within the attacked zone [Name : %s]"), *MS_FUNC_STRING, *Gate->GetName());
							MS_ENSURE(false);
						}
					}
				}
			}
		}
	}
}

bool AMS_Zone::IsWorldLocationContained(const FVector& aInWorldLocation, FVector& aOutZoneLocation) const
{
	if (aInWorldLocation.X >= ZoneLocation.X
	&& aInWorldLocation.Y >= ZoneLocation.Y
	&& aInWorldLocation.X < ZoneLocation.X + ZoneSize.X
	&& aInWorldLocation.Y < ZoneLocation.Y + ZoneSize.Y)
	{
		aOutZoneLocation = aInWorldLocation - ZoneLocation;

		return true;
	}

	return false;
}

bool AMS_Zone::IsGridContained(const FIntVector2& aInGridPosition) const
{
	return Grids.Contains(aInGridPosition);
}

void AMS_Zone::RegisterObjectToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<UMS_PropSpaceComponent> aPropSpaceComponent)
{
	if (Grids.Contains(aGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aGridPosition);

		if (GridData.Object == nullptr)
		{
			GridData.Object = aPropSpaceComponent->GetOwner();
		}
		else
		{
#if WITH_EDITOR
			MS_ERROR(TEXT("Object data alreay exists [%s - X : %d, Y : %d]"),
				*GetActorLabel(), aGridPosition.X, aGridPosition.Y);
#endif
			MS_ENSURE(false);
		}

		if (GridData.PropSpaceComponent == nullptr)
		{
			GridData.PropSpaceComponent = aPropSpaceComponent;
		}
		else
		{
			MS_ERROR(TEXT("PropSpaceComponent data alreay exists [Zone %d - X : %d, Y : %d]"),
				ZoneIndex, aGridPosition.X, aGridPosition.Y);

			MS_ENSURE(false);
		}
	}
	else
	{
#if WITH_EDITOR
		MS_ERROR(TEXT("Object's GridPosition is not vaild [%s - X : %d, Y : %d]"),
			*GetActorLabel(), aGridPosition.X, aGridPosition.Y);
#endif
		MS_ENSURE(false);
	}
}

void AMS_Zone::UnregisterObjectToGrid(const FIntVector2& aGridPosition)
{
	if (Grids.Contains(aGridPosition))
	{
		FMS_GridData& GridData = *Grids.Find(aGridPosition);

		GridData.Object = nullptr;
		GridData.PropSpaceComponent = nullptr;
	}
	else
	{
#if WITH_EDITOR
		MS_ERROR(TEXT("Object's GridPosition is not vaild [%s - X : %d, Y : %d]"),
			*GetActorLabel(), aGridPosition.X, aGridPosition.Y);
#endif
		MS_ENSURE(false);
	}
}

void AMS_Zone::OnClickZoneOpenWidget(UMS_ZoneOpenWidget* aZoneOpenWidget)
{
	bool bBound = RequestOpenZoneDelegate.ExecuteIfBound(ZoneIndex);
}

void AMS_Zone::OnZoneOpened()
{
	if (const TObjectPtr HISMManager = gHISMMng)
	{
		if (bOpened)
		{
			// Floor
			TMap<int32, TArray<FTransform>> FloorIdToTransforms = {};
			
			for (auto& It : Grids)
			{
				It.Value.FloorMeshId = GetGridFloorMeshId(It.Value.GetGridPosition());
				if (It.Value.FloorMeshId != INDEX_NONE)
				{
					TArray<FTransform>& Transforms = FloorIdToTransforms.FindOrAdd(It.Value.FloorMeshId);
					Transforms.Emplace(FTransform(It.Value.GetGridCenterLocation()));
				}
			}

			for (auto& It : FloorIdToTransforms)
			{
				gHISMMng.AddInstances(It.Key, It.Value);
			}

			// Gate
			for(TObjectPtr<class UMS_GateUnit> GateUnit : GateUnits)
			{
				if (AMS_ActorBase* Actor = GateUnit->GetActor())
				{
					Actor->SetActorHiddenInGame(false);
				}
			}
		}

		// Zone Open Mesh
		SetZoneOpenMeshVisibility(false);
	}
}

void AMS_Zone::OnAnyZoneOpened(TWeakObjectPtr<class AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor)
{
	// Test Open Zone
	if (ZoneType == EMS_ZoneType::Passage)
	{
		if (CanOpenZone())
		{
			RequestOpenZoneDelegate.ExecuteIfBound(ZoneIndex);
		}
	}

	// Wall
	if (ZoneType == EMS_ZoneType::Pallet || ZoneType == EMS_ZoneType::Outside)
	{
		return;
	}

	if (!bOpened)
	{
		return;
	}
	
	if (const TObjectPtr HISMManager = gHISMMng)
	{
		if (aOwnerLevelScriptActor != nullptr)
		{
			// ===== Location To New Wall Datas ===== //
			TMap<FVector, FMS_WallData> LocationToNewWallDatas;
			LocationToNewWallDatas.Empty();
	
			for (int j = 0; j < ZoneGridNum.X; ++j)
			{
				// ===== Back ===== //
				FIntVector2 WallGridPosition_Back = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + FIntVector2(j, 0);

				// Test
				bool bBackGridOpened = aOwnerLevelScriptActor->IsGridOpened(WallGridPosition_Back + FIntVector2(0, -1));
				if (bBackGridOpened)
				{
					continue;
				}

				const FMS_GridData* GridData_Back = GetGrid(WallGridPosition_Back);
				if (GridData_Back)
				{
					TWeakObjectPtr<AActor> WallObject = GridData_Back->Object;
					if (AMS_Prop* WallProp = Cast<AMS_Prop>(WallObject))
					{
						if (WallProp->GetPropType() == EMS_PropType::Gate)
						{
							continue;
						}
					}
				}
			
				// Add To LocationToNewWallDatas
				FVector2D WallLocationXY_Back = FMS_GridData::ConvertGridPositionToLocation(WallGridPosition_Back, true, false);
				FVector WallLocation_Back = FVector(WallLocationXY_Back.X, WallLocationXY_Back.Y, ZoneLocation.Z);
				FRotator WallRotator_Back = FRotator(0.f, 0.f, 0.f);
				LocationToNewWallDatas.Emplace(WallLocation_Back, FMS_WallData(WallLocation_Back, WallRotator_Back));
			}
			
			for (int j = 0; j < ZoneGridNum.X; ++j)
			{
				// ===== Front ===== //
				FIntVector2 WallGridPosition_Front = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + FIntVector2(j, ZoneGridNum.Y);

				// Test
				bool bFrontGridOpened = aOwnerLevelScriptActor->IsGridOpened(WallGridPosition_Front);
				if (bFrontGridOpened)
				{
					continue;
				}

				const FMS_GridData* GridData_Front = GetGrid(WallGridPosition_Front + FIntVector2(0, -1));
				if (GridData_Front)
				{
					TWeakObjectPtr<AActor> WallObject = GridData_Front->Object;
					if (AMS_Prop* WallProp = Cast<AMS_Prop>(WallObject))
					{
						if (WallProp->GetPropType() == EMS_PropType::Gate)
						{
							continue;
						}
					}
				}
			
				// Add To LocationToNewWallDatas
				FVector2D WallLocationXY_Front = FMS_GridData::ConvertGridPositionToLocation(WallGridPosition_Front, true, false);
				FVector WallLocation_Front = FVector(WallLocationXY_Front.X, WallLocationXY_Front.Y, ZoneLocation.Z);
				FRotator WallRotator_Front = FRotator(0.f, 180.f, 0.f);
				LocationToNewWallDatas.Emplace(WallLocation_Front, FMS_WallData(WallLocation_Front, WallRotator_Front));
			}

			for (int i = 0; i < ZoneGridNum.Y; ++i)
			{
				// ===== Left ===== //
				FIntVector2 WallGridPosition_Left = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + FIntVector2(0, i);

				// Test
				bool bLeftGridOpened = aOwnerLevelScriptActor->IsGridOpened(WallGridPosition_Left + FIntVector2(-1, 0));
				if (bLeftGridOpened)
				{
					continue;
				}

				const FMS_GridData* GridData_Left = GetGrid(WallGridPosition_Left);
				if (GridData_Left)
				{
					TWeakObjectPtr<AActor> WallObject = GridData_Left->Object;
					if (AMS_Prop* WallProp = Cast<AMS_Prop>(WallObject))
					{
						if (WallProp->GetPropType() == EMS_PropType::Gate)
						{
							continue;
						}
					}
				}
			
				// Add To LocationToNewWallDatas
				FVector2D WallLocationXY_Left = FMS_GridData::ConvertGridPositionToLocation(WallGridPosition_Left, false, true);
				FVector WallLocation_Left = FVector(WallLocationXY_Left.X, WallLocationXY_Left.Y, ZoneLocation.Z);
				FRotator WallRotator_Left = FRotator(0.f, 270.f, 0.f);
				LocationToNewWallDatas.Emplace(WallLocation_Left, FMS_WallData(WallLocation_Left, WallRotator_Left));
			}
			
			for (int i = 0; i < ZoneGridNum.Y; ++i)
			{
				// ===== Right ===== //
				FIntVector2 WallGridPosition_Right = FIntVector2(ZoneWorldGridPosition.X, ZoneWorldGridPosition.Y) + FIntVector2(ZoneGridNum.Y, i);

				// Test
				bool bRightGridOpened = aOwnerLevelScriptActor->IsGridOpened(WallGridPosition_Right);
				if (bRightGridOpened)
				{
					continue;
				}

				const FMS_GridData* GridData_Right = GetGrid(WallGridPosition_Right + FIntVector2(-1, 0));
				if (GridData_Right)
				{
					TWeakObjectPtr<AActor> WallObject = GridData_Right->Object;
					if (AMS_Prop* WallProp = Cast<AMS_Prop>(WallObject))
					{
						if (WallProp->GetPropType() == EMS_PropType::Gate)
						{
							continue;
						}
					}
				}
			
				// Add To LocationToNewWallDatas
				FVector2D WallLocationXY_Right = FMS_GridData::ConvertGridPositionToLocation(WallGridPosition_Right, false, true);
				FVector WallLocation_Right = FVector(WallLocationXY_Right.X, WallLocationXY_Right.Y, ZoneLocation.Z);
				FRotator WallRotator_Right = FRotator(0.f, 90.f, 0.f);
				LocationToNewWallDatas.Emplace(WallLocation_Right, FMS_WallData(WallLocation_Right, WallRotator_Right));
			}
			
			int32 WallMeshId = GetWallMeshId();

			if (WallMeshId != INDEX_NONE)
			{
				// ===== Remove Wall Mesh ===== //
				TArray<FVector> RemoveLocations;
				
				TArray<FVector> Keys;
				LocationToWallDatas.GetKeys(Keys);
			
				for (const FVector& Key : Keys)
				{
					if (LocationToNewWallDatas.Contains(Key))
					{
						LocationToNewWallDatas.Remove(Key);
					}
					else
					{
						FMS_WallData* pWallData = LocationToWallDatas.Find(Key);
						if (pWallData != nullptr && pWallData->WallMeshId != INDEX_NONE)
						{
							RemoveLocations.Emplace(Key);
						}
					
						LocationToWallDatas.Remove(Key);
					}
				}

				if (!gHISMMng.RemoveInstances(WallMeshId, RemoveLocations))
				{
					MS_ENSURE(false);
				}
			
				// ===== Add Wall Mesh ===== //
				TArray<FTransform> WallTransforms;
				WallTransforms.Empty();
		
				for (auto& It : LocationToNewWallDatas)
				{
					FMS_WallData WallData = It.Value;
					WallData.WallMeshId = WallMeshId;
					LocationToWallDatas.Emplace(It.Key, WallData);
					
					FTransform Transform;
					Transform.SetLocation(It.Value.Location);
					Transform.SetRotation(It.Value.Rotator.Quaternion());
					WallTransforms.Emplace(Transform);
				}

				gHISMMng.AddInstances(WallMeshId, WallTransforms);
			}
		}
	}
}

bool AMS_Zone::CanOpenZone()
{
	if (bOpened)
	{
		return false;
	}
	
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return false;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return false;
	}
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return false;
	}

	const TArray<int32>& OpenedZoneIds = PlayerState->GetOpenedZoneIds();

	if (ZoneType == EMS_ZoneType::Passage)
	{
		for (int32 TestId : TestConditionZoneIds)
		{
			if (!OpenedZoneIds.Contains(TestId))
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		for (int32 TestId : TestConditionZoneIds)
		{
			if (OpenedZoneIds.Contains(TestId))
			{
				return true;
			}
		}

		return false;
	}
}

void AMS_Zone::SetZoneOpenMeshVisibility(bool bIsZoneOpenableMode)
{
	if (ZoneOpenMeshComponent)
	{
		ZoneOpenMeshComponent->SetVisibility(bIsZoneOpenableMode && CanOpenZone());
	}
}

void AMS_Zone::SetZoneOpenWidgetVisibility(bool bIsZoneOpenableMode, bool bHiddenForced /*= false*/)
{
	if (ZoneOpenWidgetComponent)
	{
		ZoneOpenWidgetComponent->SetVisibility(!bHiddenForced && bIsZoneOpenableMode && CanOpenZone());
	}
}

const FMS_GridData* AMS_Zone::GetGrid(const FIntVector2& aGridPosition) const
{
	if (!Grids.Contains(aGridPosition))
	{
		return nullptr;
	}
	
	return Grids.Find(aGridPosition);
}

void AMS_Zone::ShowDebugZoneData()
{
#if WITH_EDITOR
	for (int i = 0; i < ZoneGridNum.Y; ++i)
	{
		for (int j = 0; j < ZoneGridNum.X; ++j)
		{
			if (FMS_GridData* pGrid = Grids.Find(FIntVector2(j, i)))
			{
				if (pGrid->Object != nullptr && pGrid->PropSpaceComponent != nullptr)
				{
					MS_LOG_VERBOSITY(VeryVerbose, TEXT("ZoneGrid %d-%d,%d : %s, SpaceType : %d, PurposeType : %d"),
						ZoneIndex, j, i, *pGrid->Object->GetName(),
						static_cast<uint8>(pGrid->PropSpaceComponent->GetPropSpaceType()),
						static_cast<uint8>(pGrid->PropSpaceComponent->GetPropPurposeSpaceType()));
				}
			}
		}
	}
#endif
}

void AMS_Zone::SetGridViewByTarget(TWeakObjectPtr<AMS_Prop> aLinkedProp,
	const TArray<FIntVector2>& aPreviewPropGridPositions, bool bShowSelected)
{
	TMap<int32, TArray<FVector>> FloorIdToRemoveLocations = {};
	TMap<int32, TArray<FTransform>> FloorIdToAddTransforms = {};
	
	for (auto& Grid : Grids)
	{
		int32 NewMeshId = 0;
		
		// 프리뷰 프롭이 차지하는 공간
		if (bShowSelected && aPreviewPropGridPositions.Contains(Grid.Value.GetGridPosition()))
		{
			if (Grid.Value.Object == nullptr || Grid.Value.Object == aLinkedProp)
			{
				NewMeshId = GetGridFloorMeshId(Grid.Key, EMS_FloorState::Selected);
			}
			else
			{
				NewMeshId = GetGridFloorMeshId(Grid.Key, EMS_FloorState::SelectedUnconstructable);
			}
		}

		// 프리뷰 프롭이 차지하는 공간이 아님
		else
		{
			if (Grid.Value.Object == nullptr || Grid.Value.Object == aLinkedProp)
			{
				NewMeshId = GetGridFloorMeshId(Grid.Key, EMS_FloorState::Normal);
			}
			else
			{
				NewMeshId = GetGridFloorMeshId(Grid.Key, EMS_FloorState::Unconstructable);
			}
		}

		if (Grid.Value.FloorMeshId != NewMeshId)
		{
			if (NewMeshId != INDEX_NONE)
			{
				TArray<FVector>& RemoveLocations = FloorIdToRemoveLocations.FindOrAdd(Grid.Value.FloorMeshId);
				RemoveLocations.Emplace(Grid.Value.GetGridCenterLocation());
				
				TArray<FTransform>& AddTransforms = FloorIdToAddTransforms.FindOrAdd(NewMeshId);
				AddTransforms.Emplace(FTransform(Grid.Value.GetGridCenterLocation()));

				Grid.Value.FloorMeshId = NewMeshId;
			}
		}
	}

	for (auto& It : FloorIdToRemoveLocations)
	{
		gHISMMng.RemoveInstances(It.Key, It.Value);
	}
	
	for (auto& It : FloorIdToAddTransforms)
	{
		gHISMMng.AddInstances(It.Key, It.Value);
	}
}

void AMS_Zone::SetAllGridView(EMS_FloorState aFloorState /*= EMS_FloorState::Normal*/)
{
	TMap<int32, TArray<FVector>> FloorIdToRemoveLocations = {};
	TMap<int32, TArray<FTransform>> FloorIdToAddTransforms = {};

	for (auto& Grid : Grids)
	{
		int32 NewMeshId = GetGridFloorMeshId(Grid.Key, aFloorState);
		if (Grid.Value.FloorMeshId != NewMeshId)
		{
			if (NewMeshId != INDEX_NONE)
			{
				TArray<FVector>& RemoveLocations = FloorIdToRemoveLocations.FindOrAdd(Grid.Value.FloorMeshId);
				RemoveLocations.Emplace(Grid.Value.GetGridCenterLocation());
				
				TArray<FTransform>& AddTransforms = FloorIdToAddTransforms.FindOrAdd(NewMeshId);
				AddTransforms.Emplace(FTransform(Grid.Value.GetGridCenterLocation()));

				Grid.Value.FloorMeshId = NewMeshId;
			}
		}
	}
	
	for (auto& It : FloorIdToRemoveLocations)
	{
		gHISMMng.RemoveInstances(It.Key, It.Value);
	}
	
	for (auto& It : FloorIdToAddTransforms)
	{
		gHISMMng.AddInstances(It.Key, It.Value);
	}
}

int32 AMS_Zone::GetGridFloorMeshId(const FIntVector2& aGridPosition, EMS_FloorState aFloorState /*= EMS_FloorState::Normal*/) const
{
	switch (aFloorState)
	{
	case EMS_FloorState::Normal :
		{
			if (ZoneType == EMS_ZoneType::Pallet || ZoneType == EMS_ZoneType::Outside)
			{
				return 1003;
			}

			else
			{
				if ((aGridPosition.X + aGridPosition.Y) % 2 == 0)
				{
					return 1001;
				}
				else
				{
					return 1002;
				}
			}
		}

	case EMS_FloorState::Unconstructable :
		{
			return 1004;
		}

	case EMS_FloorState::Selected :
		{
			return 1005;
		}

	case EMS_FloorState::SelectedUnconstructable :
		{
			return 1006;
		}

	default:
		{
			return 1001;
		}
	}
}

int32 AMS_Zone::GetWallMeshId() const
{
	return 1007;
}

