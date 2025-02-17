

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "MS_GridBFS_2x2.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GridBFS_2x2 : public UObject
{
	GENERATED_BODY()

public:
	UMS_GridBFS_2x2();
	
	void CollectMovingPoints();

private:
	void CollectDisplayMovingPoints();
	void CollectShelfMovingPoints();
	void CollectPalletMovingPoints();
	
	void Search(TArray<FIntVector2>& aOutPath, const FIntVector2& aStartPoint, const TArray<FIntVector2>& aTargetPoints) const;
	
private:
	TArray<FIntVector2> DisplayFreeMovableGridPoints = {};
	TArray<FIntVector2> DisplayFreeMovableWalkingPoints = {};

	TArray<FIntVector2> ShelfFreeMovableGridPoints = {};
	TArray<FIntVector2> ShelfFreeMovableWalkingPoints = {};

	TArray<FIntVector2> PalletFreeMovableGridPoints = {};
	TArray<FIntVector2> PalletFreeMovableWalkingPoints = {};

	// 등록 순서가 탐색 우선순위와 같음
	const TArray<FIntVector2> TestAddedPoints ={
		FIntVector2(0, -1),	// Front
		FIntVector2(1, 0),	// Right
		FIntVector2(-1, 0),	// Left
		FIntVector2(0, 1)};	// Back
};
