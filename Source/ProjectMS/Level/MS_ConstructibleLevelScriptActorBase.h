// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "Level/MS_LevelDefine.h"
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
	virtual void ParsingDefaultPropDatas();

public:
	virtual void RegisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas, TWeakObjectPtr<class UMS_PropSpaceComponent> aPropSpaceComponent);
	virtual void RegisterGridObjectData(TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces);

	virtual void UnregisterGridObjectData(TArray<const FMS_GridData*>& aGridDatas);
	virtual void UnregisterGridObjectData(TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces);
	
	bool GetGridDatasForAllPropSpaceLocations(class AMS_Prop* aInProp, TArray<FMS_GridDataForPropSpace>& aOutGridDatasForPropSpaces, const FIntVector2& aInAddtiveGridPosition = FIntVector2::ZeroValue);	// Ret : AllGridInZones
	bool GetGridDatasForPropSpaceLocations(class UMS_PropSpaceComponent* aPropSpaceComponent, TArray<const FMS_GridData*>& aOutGridDatas, const FIntVector2& aInAddtiveGridPosition = FIntVector2::ZeroValue);	// Ret : AllGridInZones

	int32 GetGridZoneIndex(const FIntVector2& aGridPosition) const;
	bool IsGridOpened(const FIntVector2& aGridPosition) const;

	UFUNCTION()
	void OnZoneOpened();
	
	void ShowUnconstructableGrid(bool bShow);
	
protected:
	UPROPERTY()
	bool HasBegun;
	
	UPROPERTY(EditAnywhere)
	TMap<int32, TObjectPtr<class AMS_Zone>> Zones;

	bool bShowUnconstructableGrid;
};
