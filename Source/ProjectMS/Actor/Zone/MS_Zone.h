// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "MS_Zone.generated.h"


DECLARE_DELEGATE_OneParam(FMS_RequestOpenZoneDelegate, int32);

UCLASS()
class PROJECTMS_API AMS_Zone : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	AMS_Zone(const FObjectInitializer& aObjectInitializer);

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

private:
	void InitializeZoneData();
	
	void CreateGrids();

	void RegisterDefalutAttachedProps();


public:
	bool IsWorldLocationContained(const FVector& aInWorldLocation, FVector& aOutZoneLocation) const;
	bool IsGridContained(const FIntVector2& aInGridPosition) const;
	
	void RegisterObjectToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<class UMS_PropSpaceComponent> aPropSpaceComponent);
	void UnregisterObjectToGrid(const FIntVector2& aGridPosition);

	// Zone Open
	UFUNCTION()
	void OnClickZoneOpenWidget(class UMS_ZoneOpenWidget* aZoneOpenWidget);
	
	void SetZoneOpened(bool aOpened) { bOpened = aOpened; }

	void OnZoneOpened();
	void OnAnyZoneOpened(TWeakObjectPtr<class AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor);
	
	bool CanOpenZone();

	void SetZoneOpenMeshVisibility(bool bIsZoneOpenableMode);
	void SetZoneOpenWidgetVisibility(bool bIsZoneOpenableMode, bool bHiddenForced = false);

	
	// Getter
	FORCEINLINE int32 GetZoneIndex() const { return ZoneIndex; }
	FORCEINLINE int32 GetZonePrice() const { return ZonePrice; }
	FORCEINLINE EMS_ZoneType GetZoneType() const { return ZoneType; }

	FORCEINLINE const TArray<int32>& GetTestConditionZoneIds() const { return TestConditionZoneIds; }
	
	FORCEINLINE const FVector& GetZoneLocation() const { return ZoneLocation; }
	
	FORCEINLINE const FIntVector2& GetZoneGridNum() const { return ZoneGridNum; }
	
	FORCEINLINE const FIntVector2& GetZoneWorldGridPosition() const { return ZoneWorldGridPosition; }

	FORCEINLINE const TMap<FIntVector2, FMS_GridData>& GetGrids() const { return Grids; }

	FORCEINLINE bool IsOpened() const { return bOpened; }
	
	const FMS_GridData* GetGrid(const FIntVector2& aGridPosition) const;

	FORCEINLINE void GetGateUnits(TArray<class UMS_GateUnit*>& aOutGateUnits) const
	{
		aOutGateUnits = GateUnits;
	}

	void ShowDebugZoneData();

	void SetGridViewByTarget(TWeakObjectPtr<class AMS_Prop> aLinkedProp, const TArray<FIntVector2>& aPreviewPropGridPositions, bool bShowSelected);
	void SetAllGridView(EMS_FloorState aFloorState /*= EMS_FloorState::Normal*/);
	
	int32 GetGridFloorMeshId(const FIntVector2& aGridPosition, EMS_FloorState aFloorState = EMS_FloorState::Normal) const;
	int32 GetWallMeshId() const;
	
protected:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ZoneBoxComponent;

	// Zone Open
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> ZoneOpenMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> ZoneOpenWidgetComponent;


private:
	// Zone Data
	UPROPERTY(EditInstanceOnly, Category=MS_ZoneInfo)
	int32 ZoneIndex = 0;

	UPROPERTY(EditInstanceOnly, Category=MS_ZoneInfo)
	int32 ZonePrice = 0;
	
	UPROPERTY(EditInstanceOnly, Category=MS_ZoneInfo)
	EMS_ZoneType ZoneType = EMS_ZoneType::None;

	UPROPERTY(EditInstanceOnly, Category=MS_ZoneInfo)
	TArray<int32> TestConditionZoneIds = {};
	
	UPROPERTY()
	FVector ZoneLocation = FVector::ZeroVector;

	UPROPERTY()
	FVector ZoneSize = FVector::ZeroVector;
	
	UPROPERTY()
	FIntVector2 ZoneGridNum = FIntVector2::NoneValue;

	UPROPERTY()
	FIntVector2 ZoneWorldGridPosition = FIntVector2::NoneValue;

	UPROPERTY()
	bool bOpened = false;
	
	UPROPERTY()
	TMap<FIntVector2, FMS_GridData> Grids = {};

	UPROPERTY()
	TMap<FVector, FMS_WallData> LocationToWallDatas = {};

	UPROPERTY()
	TArray<TObjectPtr<class UMS_GateUnit>> GateUnits = {};

public:
	FMS_RequestOpenZoneDelegate RequestOpenZoneDelegate;
};
