// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase.h"

#include "MS_Define.h"
#include "Kismet/GameplayStatics.h"

#include "Prop/MS_Prop.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/RowBase/MS_FurnitureData.h"
#include "Units/MS_FurnitureUnit.h"
#include "Units/MS_GateUnit.h"
#include "Zone/MS_Zone.h"


AMS_ConstructibleLevelScriptActorBase::AMS_ConstructibleLevelScriptActorBase()
	: HasBegun(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_ConstructibleLevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (!HasBegun)
	{
		HasBegun = true;
		
		InitializeZones();
	}
}

void AMS_ConstructibleLevelScriptActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_ConstructibleLevelScriptActorBase::InitializeZones()
{
	// Zone
	TArray<AActor*> ZoneActors;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Zone::StaticClass(), ZoneActors);
	
	for (auto& ZoneActor : ZoneActors)
	{
		if (AMS_Zone* Zone = Cast<AMS_Zone>(ZoneActor))
		{
			if (Zones.Contains(Zone->GetZoneIndex()))
			{
				MS_ERROR(TEXT("[%s] ZoneId is alreay exist [Id : %d]"), *MS_FUNC_STRING, Zone->GetZoneIndex());
				MS_CHECK(false);
			}
			
			Zones.Emplace(Zone->GetZoneIndex(), Zone);
			
			Zone->RequestOpenZoneDelegate.BindUObject(this, &AMS_ConstructibleLevelScriptActorBase::RequestOpenZone);
		}
	}
	
	InitializeOpenedZoneStates();
}

void AMS_ConstructibleLevelScriptActorBase::RegisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas,
	TWeakObjectPtr<UMS_PropSpaceComponent> aPropSpaceComponent)
{
	for (const FMS_GridData* GridData : aGridDatas)
	{
		AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
		Zone->RegisterObjectToGrid(GridData->GetGridPosition(), aPropSpaceComponent);
	}
}

void AMS_ConstructibleLevelScriptActorBase::RegisterGridObjectData(
	TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces)
{
	for (const FMS_GridDataForPropSpace& GridDataForPropSpace : aGridDatasForPropSpaces)
	{
		UMS_PropSpaceComponent* PropSpaceComponent = GridDataForPropSpace.PropSpaceComponent;
		if (!IsValid(PropSpaceComponent))
		{
			MS_ENSURE(false);
			return;
		}
		
		TArray<const FMS_GridData*> GridDatas = GridDataForPropSpace.GridDatas;
		
		for (const FMS_GridData* GridData : GridDatas)
		{
			AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
			Zone->RegisterObjectToGrid(GridData->GetGridPosition(), PropSpaceComponent);
		}
	}
}

void AMS_ConstructibleLevelScriptActorBase::UnregisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas)
{
	for (const FMS_GridData* GridData : aGridDatas)
	{
		AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
		Zone->UnregisterObjectToGrid(GridData->GetGridPosition());
	}
}

void AMS_ConstructibleLevelScriptActorBase::UnregisterGridObjectData(
	TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces)
{
	for (const FMS_GridDataForPropSpace& GridDataForPropSpace : aGridDatasForPropSpaces)
	{
		TArray<const FMS_GridData*> GridDatas = GridDataForPropSpace.GridDatas;
		
		for (const FMS_GridData* GridData : GridDatas)
		{
			AMS_Zone* Zone = Cast<AMS_Zone>(GridData->GetOwnerZone());
			Zone->UnregisterObjectToGrid(GridData->GetGridPosition());
		}
	}
}

bool AMS_ConstructibleLevelScriptActorBase::GetGridDatasForAllPropSpaceLocations(AMS_Prop* aInProp,
                                                                                 TArray<FMS_GridDataForPropSpace>& aOutGridDatasForPropSpaces, const FIntVector2& aInAddtiveGridPosition) // Ret : AllGridInZones
{
	if (!IsValid(aInProp))
	{
		return false;
	}
	
	if (aInProp->GetPropType() != EMS_PropType::Furniture && aInProp->GetPropType() != EMS_PropType::Structure)
	{
		return true;
	}

	aOutGridDatasForPropSpaces.Empty();
	
	const TArray<UMS_PropSpaceComponent*>& PropSpaceComponents = aInProp->GetPropSpaceComponents();
		
	for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
	{
		FMS_GridDataForPropSpace GridDataForPropSpace;
		GridDataForPropSpace.PropSpaceComponent = PropSpaceComponent;
		
		FIntVector2 StartGridPosition = FIntVector2::ZeroValue;
		FIntVector2 GridNum = FIntVector2::ZeroValue;
			
		PropSpaceComponent->GetGridPositions(StartGridPosition, GridNum);
		StartGridPosition += aInAddtiveGridPosition;
		
		// Set With Grid
		for (int i = 0; i < GridNum.Y; ++i)
		{
			for (int j = 0; j < GridNum.X; ++j)
			{
				FIntVector2 GridPosition = FIntVector2(StartGridPosition.X + j, StartGridPosition.Y + i);

				int32 ZoneIndex = GetGridZoneIndex(GridPosition);

				if (ZoneIndex == INDEX_NONE)
				{
					return false;
				}

				AMS_Zone* Zone = *Zones.Find(ZoneIndex);
				if (!IsValid(Zone) || !Zone->IsOpened())
				{
					return false;
				}
				
				const FMS_GridData* GridData = (*Zones.Find(ZoneIndex))->GetGrid(GridPosition);
				if (GridData == nullptr)
				{
					return false;
				}

				GridDataForPropSpace.GridDatas.Emplace(GridData);
			}
		}

		aOutGridDatasForPropSpaces.Emplace(GridDataForPropSpace);
	}

	return true;
}

bool AMS_ConstructibleLevelScriptActorBase::GetGridDatasForPropSpaceLocations(
	UMS_PropSpaceComponent* aPropSpaceComponent, TArray<const FMS_GridData*>& aOutGridDatas,
	const FIntVector2& aInAddtiveGridPosition)
{
	if (!IsValid(aPropSpaceComponent))
	{
		return false;
	}

	AMS_Prop* OwnerProp = aPropSpaceComponent->GetOwnerProp();
	if (!IsValid(OwnerProp))
	{
		return false;
	}
	
	if (OwnerProp->GetPropType() != EMS_PropType::Furniture && OwnerProp->GetPropType() != EMS_PropType::Structure)
	{
		return true;
	}

	aOutGridDatas.Empty();
	
	FIntVector2 StartGridPosition = FIntVector2::ZeroValue;
	FIntVector2 GridNum = FIntVector2::ZeroValue;
		
	aPropSpaceComponent->GetGridPositions(StartGridPosition, GridNum);
	StartGridPosition += aInAddtiveGridPosition;
	
	// Set With Grid
	for (int i = 0; i < GridNum.Y; ++i)
	{
		for (int j = 0; j < GridNum.X; ++j)
		{
			FIntVector2 GridPosition = FIntVector2(StartGridPosition.X + j, StartGridPosition.Y + i);

			int32 ZoneIndex = GetGridZoneIndex(GridPosition);

			if (ZoneIndex == INDEX_NONE)
			{
				return false;
			}

			AMS_Zone* Zone = *Zones.Find(ZoneIndex);
			if (!IsValid(Zone) || !Zone->IsOpened())
			{
				return false;
			}
				
			const FMS_GridData* GridData = (*Zones.Find(ZoneIndex))->GetGrid(GridPosition);
			if (GridData == nullptr)
			{
				return false;
			}

			aOutGridDatas.Emplace(GridData);
		}
	}

	return true;
}

int32 AMS_ConstructibleLevelScriptActorBase::GetGridZoneIndex(const FIntVector2& aGridPosition) const
{
	for (auto& Zone : Zones)
	{
		if (Zone.Value->IsGridContained(aGridPosition))
		{
			return Zone.Key;
		}
	}

	// MS_Ensure(false);
	return INDEX_NONE;
}

EMS_ZoneType AMS_ConstructibleLevelScriptActorBase::GetGridZoneType(const FIntVector2& aGridPosition) const
{
	for (auto& Zone : Zones)
	{
		if (Zone.Value->IsGridContained(aGridPosition))
		{
			return Zone.Value->GetZoneType();
		}
	}

	// MS_Ensure(false);
	return EMS_ZoneType::None;
}

bool AMS_ConstructibleLevelScriptActorBase::IsGridOpened(const FIntVector2& aGridPosition) const
{
	int32 GridZoneIndex = GetGridZoneIndex(aGridPosition);
	if (GridZoneIndex == INDEX_NONE)
	{
		return false;
	}

	AMS_Zone* Zone = *Zones.Find(GridZoneIndex); // GetGridZoneIndex에서 ContainsCheck 완료
	if (IsValid(Zone))
	{
		return Zone->IsOpened();
	}

	return false;
}

void AMS_ConstructibleLevelScriptActorBase::GetAllGateUnitsInLevel(TArray<UMS_GateUnit*>& OutGateUnits) const
{
	OutGateUnits.Empty();
	for (auto& Zone : Zones)
	{
		TArray<UMS_GateUnit*> ZoneGatesUnits;
		Zone.Value->GetGateUnits(ZoneGatesUnits);

		OutGateUnits.Append(ZoneGatesUnits);
	}
}

void AMS_ConstructibleLevelScriptActorBase::GetGateUnitsInLevel(TArray<TWeakObjectPtr<UMS_GateUnit>>& OutGateUnits,
	EMS_ZoneType ZoneType, EMS_ZoneType LinkedZoneType) const
{
	TArray<UMS_GateUnit*> GateUnits;
	GetAllGateUnitsInLevel(GateUnits);

	for (UMS_GateUnit* GateUnit : GateUnits)
	{
		if (GateUnit->GetGateZoneType() == ZoneType
			&& GateUnit->GetLinkedZoneType() == LinkedZoneType)
		{
			OutGateUnits.Emplace(GateUnit);
		}
	}
}

TWeakObjectPtr<AActor> AMS_ConstructibleLevelScriptActorBase::GetGridObject(const FIntVector2& aGridPosition) const
{
	int32 GridZoneIndex = GetGridZoneIndex(aGridPosition);
	if (GridZoneIndex == INDEX_NONE)
	{
		return nullptr;
	}

	AMS_Zone* Zone = *Zones.Find(GridZoneIndex); // GetGridZoneIndex에서 ContainsCheck 완료
	if (IsValid(Zone))
	{
		const FMS_GridData* GridData = Zone->GetGrid(aGridPosition);
		if (GridData)
		{
			return GridData->Object;
		}
	}

	return nullptr;
}

TWeakObjectPtr<UMS_PropSpaceComponent> AMS_ConstructibleLevelScriptActorBase::GetGridPropSpace(
	const FIntVector2& aGridPosition) const
{
	int32 GridZoneIndex = GetGridZoneIndex(aGridPosition);
	if (GridZoneIndex == INDEX_NONE)
	{
		return nullptr;
	}

	AMS_Zone* Zone = *Zones.Find(GridZoneIndex); // GetGridZoneIndex에서 ContainsCheck 완료
	if (IsValid(Zone))
	{
		const FMS_GridData* GridData = Zone->GetGrid(aGridPosition);
		if (GridData)
		{
			if (GridData->Object != nullptr)
			{
				return GridData->PropSpaceComponent;
			}
		}
	}

	return nullptr;
}

void AMS_ConstructibleLevelScriptActorBase::InitializeOpenedZoneStates()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}
	
	const TArray<int32>& OpenedZoneIds = PlayerState->GetOpenedZoneIds();

	for (int32 OpenedZoneId : OpenedZoneIds)
	{
		if (Zones.Contains(OpenedZoneId))
		{
			AMS_Zone* OpenedZone = *Zones.Find(OpenedZoneId);

			if (IsValid(OpenedZone))
			{
				OpenedZone->SetZoneOpened(true);
			}
		}
	}
	
	for (auto& Zone : Zones)
	{
		if (Zone.Value->IsOpened())	// 이 Function에서 새로 열린 존과 각 존 BeginPlay에서 미리 열려있던 존 모두 적용
		{
			Zone.Value->OnZoneOpened();
		}
		
		Zone.Value->OnAnyZoneOpened(this);
	}
}

void AMS_ConstructibleLevelScriptActorBase::RequestOpenZone(int32 aZoneIndex)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}
	
	if (!Zones.Contains(aZoneIndex))
	{
		MS_ERROR(TEXT("[%s] Requested ZoneIndex is invalid [Id : %d]"), *MS_FUNC_STRING, aZoneIndex);
		MS_ENSURE (false);
	}

	AMS_Zone* Zone = *Zones.Find(aZoneIndex);
	if (!IsValid(Zone))
	{
		MS_ERROR(TEXT("[%s] Zone is invalid [Id : %d]"), *MS_FUNC_STRING, aZoneIndex);
		MS_ENSURE (false);
	}
	
	const TArray<int32>& OpenedZoneIds = PlayerState->GetOpenedZoneIds();
	if (OpenedZoneIds.Contains(aZoneIndex))
	{
		MS_LOG_VERBOSITY(Warning, TEXT("[%s] Zone is alreay opened [Id : %d]"), *MS_FUNC_STRING, aZoneIndex);
		return;
	}

	if (Zone->CanOpenZone())
	{
		Zone->SetZoneOpened(true);

		if (Zone->GetZoneType() == EMS_ZoneType::Display
			|| Zone->GetZoneType() == EMS_ZoneType::Shelf)
		{
			PlayerState->AddOpenedZoneId(aZoneIndex);
			PlayerState->SettleMoney((-1) * Zone->GetZonePrice());
			gItemMng.OnUpdateEarnMoneyDelegate.Broadcast(true);
			PlayerState->SavePlayerData();
		}
		
		OnZoneOpened(Zone);
	}

	gModeMng.OnUpdateZoneDelegate.Broadcast();
}

void AMS_ConstructibleLevelScriptActorBase::OnZoneOpened(AMS_Zone* aZone)
{
	if (IsValid(aZone))
	{
		aZone->OnZoneOpened();
		
		for (auto& Zone : Zones)
		{
			if (Zone.Value->IsOpened())
			{
				Zone.Value->OnAnyZoneOpened(this);
			}
		}
		
		SetZoneOpenableView(gModeMng.GetCurrentModeStateId() == EMS_ModeState::Construct);
	}
}

void AMS_ConstructibleLevelScriptActorBase::SetZoneOpenableView(bool bZoneOpenableMode)
{
	for (auto& Zone : Zones)
	{
		Zone.Value->SetZoneOpenMeshVisibility(bZoneOpenableMode);
		Zone.Value->SetZoneOpenWidgetVisibility(bZoneOpenableMode);
	}
}

void AMS_ConstructibleLevelScriptActorBase::SetZoneOpenWidgetVisibility(bool bHiddenWidgetForced)
{
	bool bZoneOpenableMode = gModeMng.GetCurrentModeStateId() == EMS_ModeState::Construct;

	for (auto& Zone : Zones)
	{
		Zone.Value->SetZoneOpenWidgetVisibility(bZoneOpenableMode, bHiddenWidgetForced);
	}
}

void AMS_ConstructibleLevelScriptActorBase::UpdateConstructableGridView(bool bShow, TWeakObjectPtr<AMS_Prop> aTargetPreviewProp, bool bShowSelected)
{
	if (bShow)
	{
		TWeakObjectPtr<AMS_Prop> LinkedProp = nullptr;
		TArray<FIntVector2> PreviewPropGridPositions = {};
		EMS_ZoneType ConstructibleZoneType = EMS_ZoneType::None;
		
		if (aTargetPreviewProp != nullptr)
		{
			LinkedProp = aTargetPreviewProp->GetLinkedProp();
			ConstructibleZoneType = aTargetPreviewProp->GetConstructableZoneType();
			
			if (bShowSelected)
			{
				aTargetPreviewProp->GetAllGridPositions(PreviewPropGridPositions);
			}
		}
	
		for (auto& Zone : Zones)
		{
			if (Zone.Value->IsOpened())
			{
				// 설치할 수 없는 ZoneType 일때
				if (aTargetPreviewProp != nullptr)
				{
					if (ConstructibleZoneType != Zone.Value->GetZoneType())
					{
						Zone.Value->SetAllGridView(EMS_FloorState::Unconstructable);
						continue;
					}
				}

				// 설치할 수 있는 ZoneType 일때
				Zone.Value->SetGridViewByTarget(LinkedProp, PreviewPropGridPositions, bShowSelected);
			}
		}
	}

	else
	{
		for (auto& Zone : Zones)
		{
			if (Zone.Value->IsOpened())
			{
				Zone.Value->SetAllGridView(EMS_FloorState::Normal);
			}
		}
	}
}

TWeakObjectPtr<UMS_FurnitureUnit> AMS_ConstructibleLevelScriptActorBase::CreateProp(EMS_PropType aPropType, int32 aTableIndex, const FIntVector2& aGridPosition,
	const EMS_Rotation aRotation)
{
	// ToDo : 다양한 Prop 타입에 대응
	MS_CHECK(aPropType == EMS_PropType::Furniture);

	// Data
	FMS_FurnitureData* FurnitureTableData = gTableMng.GetTableRowData<FMS_FurnitureData>(EMS_TableDataType::Furniture, aTableIndex);
	MS_ENSURE(FurnitureTableData != nullptr);

	EMS_FurnitureType FurnitureType = static_cast<EMS_FurnitureType>(FurnitureTableData->FurnitureType);

	if (!FurnitureUnitMap::FurnitureUnitTypeMap.Contains(FurnitureType))
	{
		MS_ERROR(TEXT("[%s] FurnitureType can't registered in FurnitureUnitTypeMap [Id : %d]"), *MS_FUNC_STRING, FurnitureTableData->FurnitureType)
		MS_ENSURE(false);
	}
	EMS_UnitType FurnitureUnitType = *FurnitureUnitMap::FurnitureUnitTypeMap.Find(static_cast<EMS_FurnitureType>(FurnitureType));
	
	// Calc Location
	FVector2D CenterLocationOffset = FVector2D(FurnitureTableData->ArrangementOffsetX, FurnitureTableData->ArrangementOffsetY);
	FVector2D LocationXY = FMS_GridData::ConvertGridPositionToLocation(aGridPosition) + CenterLocationOffset;
	FVector Location = FVector(LocationXY.X, LocationXY.Y, 0.f);
	FRotator Rotator = FRotator(0.f, UMS_MathUtility::ConvertRotation(aRotation), 0.f);

	// CreateUnit
	const TObjectPtr<UMS_FurnitureUnit> NewUnit = Cast<UMS_FurnitureUnit>(gUnitMng.CreateUnit(FurnitureUnitType, aTableIndex, true, Location, Rotator));
	if (!IsValid(NewUnit))
	{
		MS_ENSURE(false);
		return nullptr;
	}
				
	AMS_Prop* NewProp = Cast<AMS_Prop>(NewUnit->GetActor());
	if (!IsValid(NewProp))
	{
		MS_ENSURE(false);
		return nullptr;
	}
				
	// Register New Datas
	TArray<FMS_GridDataForPropSpace> PropGridDatas;
	GetGridDatasForAllPropSpaceLocations(NewProp, PropGridDatas);
	RegisterGridObjectData(PropGridDatas);

	return NewUnit;
}

bool AMS_ConstructibleLevelScriptActorBase::DestroyProp(TWeakObjectPtr<AMS_Prop> aProp)
{
	// ToDo : Unit을 받도록 수정
	if (aProp != nullptr)
	{
	}

	return false;
}

bool AMS_ConstructibleLevelScriptActorBase::MoveAndRotateProp(TWeakObjectPtr<AMS_Prop> aProp,
	const FIntVector2& aGridPosition, const EMS_Rotation aRotation)
{
	// ToDo : Unit을 받도록 수정
	if (aProp != nullptr)
	{
		// ToDo : 다양한 Prop 타입에 대응
		MS_CHECK(aProp->GetPropType() == EMS_PropType::Furniture);
		
		FMS_FurnitureData* FurnitureData = gTableMng.GetTableRowData<FMS_FurnitureData>(EMS_TableDataType::Furniture, aProp->GetTableIndex());
		MS_ENSURE(FurnitureData != nullptr);
	
		// Unregister Old Datas
		TArray<FMS_GridDataForPropSpace> OldLocationGridDatas;
		GetGridDatasForAllPropSpaceLocations(aProp.Get(), OldLocationGridDatas);
		UnregisterGridObjectData(OldLocationGridDatas);

		// Set Location And Rotation
		FVector2D CenterLocationOffset = FVector2D(FurnitureData->ArrangementOffsetX, FurnitureData->ArrangementOffsetY);
		FVector2D LocationXY = FMS_GridData::ConvertGridPositionToLocation(aGridPosition) + CenterLocationOffset;
		FVector Location = FVector(LocationXY.X, LocationXY.Y, 0.f);
		FRotator Rotator = FRotator(0.f, UMS_MathUtility::ConvertRotation(aRotation), 0.f);

		aProp->SetActorLocationAndRotation(Location, Rotator);

		// Register New Datas
		TArray<FMS_GridDataForPropSpace> NewLocationGridDatas;
		GetGridDatasForAllPropSpaceLocations(aProp.Get(), NewLocationGridDatas);
		RegisterGridObjectData(NewLocationGridDatas);

		return true;
	}

	return false;
}

void AMS_ConstructibleLevelScriptActorBase::GetFreeMovableGridPositions(TArray<FIntVector2>& aOutGrids,
	EMS_ZoneType aInZoneType)
{
	aOutGrids.Empty();

	for (auto& Zone : Zones)
	{
		if (Zone.Value->GetZoneType() == aInZoneType && Zone.Value->IsOpened())
		{
			const TMap<FIntVector2, FMS_GridData>& ZoneGrids = Zone.Value->GetGrids();

			for (auto& It : ZoneGrids)
			{
				if (It.Value.Object != nullptr)
				{
					if (It.Value.PropSpaceComponent != nullptr)
					{
						if (It.Value.PropSpaceComponent->GetPropSpaceType() != EMS_PropSpaceType::FreeSpace)
						{
							continue;
						}
					}
				}

				aOutGrids.Emplace(It.Key);
			}
		}
	}
}