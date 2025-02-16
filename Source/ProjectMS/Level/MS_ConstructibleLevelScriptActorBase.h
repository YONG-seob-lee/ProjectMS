// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "ContentsUtilities/MS_LevelDefine.h"
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
	bool IsGridOpened(const FIntVector2& aGridPosition) const;
	
	TWeakObjectPtr<AActor> GetGridObject(const FIntVector2& aGridPosition) const;

	void InitializeOpenedZoneStates();
	void RequestOpenZone(int32 aZoneIndex);
	
	UFUNCTION()
	void OnZoneOpened(AMS_Zone* aZone);

	void SetZoneOpenableView();
	void SetZoneOpenWidgetVisibility(bool bHiddenWidgetForced = false);
	
	void ShowUnconstructableGrid(bool bShow);

	
	// Prop
	TWeakObjectPtr<class UMS_FurnitureUnit> CreateProp(EMS_PropType aPropType, int32 aTableIndex, const FIntVector2& aGridPosition, const EMS_Rotation aRotation);
	
	bool DestroyProp(TWeakObjectPtr<class AMS_Prop> aProp);
	
	bool MoveAndRotateProp(TWeakObjectPtr<class AMS_Prop> aProp, const FIntVector2& aGridPosition, const EMS_Rotation aRotation);

	
protected:
	UPROPERTY()
	bool HasBegun;
	
	UPROPERTY()
	TMap<int32, TObjectPtr<class AMS_Zone>> Zones;

	bool bShowUnconstructableGrid;
};