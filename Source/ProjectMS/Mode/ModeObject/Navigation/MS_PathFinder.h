

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "MS_PathFinder.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PathFinder : public UObject
{
	GENERATED_BODY()

public:
	UMS_PathFinder();
	
	void CollectAllZoneTypeMovingPoints();

private:
	void CollectMovingPoints(EMS_ZoneType aCollectZoneType);

public:
	void SearchBFS(TArray<FIntVector2>& aOutPath, EMS_ZoneType aSearchZoneType, const FIntVector2& aStartPosition, const TArray<FIntVector2>& aTargetPositions, const TArray<FIntVector2>& aNotMovablePoints = {}) const;
	void SearchAStar(TArray<FIntVector2>& aOutPath, EMS_ZoneType aSearchZoneType, const FIntVector2& aStartPosition, const TArray<FIntVector2>& aTargetPositions, const TArray<FIntVector2>& aNotMovablePoints = {}) const;

	void GetTargetZoneMovablePoints(TArray<FIntVector2>& aOutPoints, EMS_ZoneType aSearchZoneType, const TArray<FIntVector2>& aNotMovablePoints = {}) const;
	
	FIntVector2 SelectHeuristicTarget(const TArray<FIntVector2>& aTargetPositions) const;
	void GetHeuristicCosts(const TArray<FIntVector2>& aPoints, const FIntVector2& aStartPosition, const FIntVector2& aHeuristicTarget, TArray<int32>& aOutCosts) const;
	
	bool GetRandomPosition(EMS_ZoneType aZoneType, FIntVector2& aOutPosition) const;
	
private:
	TArray<FIntVector2> DisplayFreeMovableWalkingPoints = {};
	TArray<FIntVector2> ShelfFreeMovableWalkingPoints = {};
	TArray<FIntVector2> PalletFreeMovableWalkingPoints = {};
	TArray<FIntVector2> OutsideFreeMovableWalkingPoints = {};

	// 등록 순서가 탐색 우선순위와 같음
	const TArray<FIntVector2> TestAddedPoints ={
		FIntVector2(0, -1),	// Front
		FIntVector2(1, 0),	// Right
		FIntVector2(-1, 0),	// Left
		FIntVector2(0, 1)};	// Back
};
