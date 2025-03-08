// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MathUtility/MS_MathUtility.h"
#include "MS_ConstructibleLevelScriptActorBase.generated.h"


UCLASS()
class PROJECTMS_API AMS_ConstructibleLevelScriptActorBase : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_ConstructibleLevelScriptActorBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
protected:
	virtual void InitializeZones();

public:
	virtual void RegisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas, TWeakObjectPtr<class UMS_PropSpaceComponent> aPropSpaceComponent);
	virtual void RegisterGridObjectData(TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces);

	virtual void UnregisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas);
	virtual void UnregisterGridObjectData(TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces);
	
	bool GetGridDatasForAllPropSpaceLocations(class AMS_Prop* aInProp, TArray<FMS_GridDataForPropSpace>& aOutGridDatasForPropSpaces, const FIntVector2& aInAddtiveGridPosition = FIntVector2::ZeroValue);	// Ret : AllGridInZones
	bool GetGridDatasForPropSpaceLocations(class UMS_PropSpaceComponent* aPropSpaceComponent, TArray<const FMS_GridData*>& aOutGridDatas, const FIntVector2& aInAddtiveGridPosition = FIntVector2::ZeroValue);	// Ret : AllGridInZones

	int32 GetGridZoneIndex(const FIntVector2& aGridPosition) const;
	EMS_ZoneType GetGridZoneType(const FIntVector2& aGridPosition) const;
	bool IsGridOpened(const FIntVector2& aGridPosition) const;

	void GetAllGateUnitsInLevel(TArray<class UMS_GateUnit*>& OutGateUnits) const;
	void GetGateUnitsInLevel(TArray<TWeakObjectPtr<class UMS_GateUnit>>& OutGateUnits, EMS_ZoneType ZoneType, EMS_ZoneType LinkedZoneType) const;
	
	TWeakObjectPtr<AActor> GetGridObject(const FIntVector2& aGridPosition) const;
	TWeakObjectPtr<class UMS_PropSpaceComponent> GetGridPropSpace(const FIntVector2& aGridPosition) const;

	void InitializeOpenedZoneStates();
	void RequestOpenZone(int32 aZoneIndex);
	
	UFUNCTION()
	void OnZoneOpened(AMS_Zone* aZone);

	void SetZoneOpenableView(bool bZoneOpenableMode);
	void SetZoneOpenWidgetVisibility(bool bHiddenWidgetForced = false);
	
	void UpdateConstructableGridView(bool bShow, TWeakObjectPtr<class AMS_Prop> aTargetPreviewProp, bool bShowSelected);

	
	// Prop
	TWeakObjectPtr<class UMS_FurnitureUnit> CreateProp(EMS_PropType aPropType, int32 aTableIndex, const FIntVector2& aGridPosition, const EMS_Rotation aRotation);
	
	bool DestroyProp(TWeakObjectPtr<class AMS_Prop> aProp);
	
	bool MoveAndRotateProp(TWeakObjectPtr<class AMS_Prop> aProp, const FIntVector2& aGridPosition, const EMS_Rotation aRotation);


	// Navigation
	void GetFreeMovableGridPositions(TArray<FIntVector2>& aOutGrids, EMS_ZoneType aInZoneType);

	
protected:
	UPROPERTY()
	bool HasBegun;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<class AMS_Zone>> Zones;
};