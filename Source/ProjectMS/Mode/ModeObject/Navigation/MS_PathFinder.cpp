﻿#include "MS_PathFinder.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "Manager_Client/MS_SceneManager.h"
#include "MathUtility/MS_PriorityQueue.h"
#include "Util/IndexPriorityQueue.h"


UMS_PathFinder::UMS_PathFinder()
{
}

void UMS_PathFinder::CollectAllZoneTypeMovingPoints()
{
	CollectMovingPoints(EMS_ZoneType::Display);
	CollectMovingPoints(EMS_ZoneType::Shelf);
	CollectMovingPoints(EMS_ZoneType::Pallet);
	CollectMovingPoints(EMS_ZoneType::Outside);
}

void UMS_PathFinder::CollectMovingPoints(EMS_ZoneType aCollectZoneType)
{
	TArray<FIntVector2> FreeMovableGridPositions;
	FreeMovableGridPositions.Empty();
	
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		LevelScriptActor->GetFreeMovableGridPositions(FreeMovableGridPositions, aCollectZoneType);

		// O 그리드를 좌상단 좌표 기준으로 3방향 그리드가 있는지 확인
		// XX
		// XO
		for (const FIntVector2& GridPosition : FreeMovableGridPositions)
		{
			// Check
			if (!FreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, -1)))
			{
				continue;
			}

			if (!FreeMovableGridPositions.Contains(GridPosition + FIntVector2(0, -1)))
			{
				continue;
			}

			if (!FreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, 0)))
			{
				continue;
			}

			// Add
			switch (aCollectZoneType)
			{
			case EMS_ZoneType::Display :
				{
					DisplayFreeMovableWalkingPoints.Add(GridPosition);
					break;
				}

			case EMS_ZoneType::Shelf :
				{
					ShelfFreeMovableWalkingPoints.Add(GridPosition);
					break;
				}

			case EMS_ZoneType::Pallet :
				{
					PalletFreeMovableWalkingPoints.Add(GridPosition);
					break;
				}

			case EMS_ZoneType::Outside :
				{
					OutsideFreeMovableWalkingPoints.Add(GridPosition);
					break;
				}

			default:
				{
					MS_ENSURE(false);
					return;
				}
			}
		}
	}
}


void UMS_PathFinder::SearchBFS(TArray<FIntVector2>& aOutPath, EMS_ZoneType aSearchZoneType,
	const FIntVector2& aStartPosition, const TArray<FIntVector2>& aTargetPositions,
	const TArray<FIntVector2>& aNotMovablePoints) const
{
	// 다른 타입의 존일때 Gate까지만 계산해서 계산량을 줄임
	// 따라서 인자로 같은 존의 값이 넘어오게 됨
	// ToDo : 같은 존 타입 사이에 Gate를 두게 됐을때 aSearchZoneType 인자를 더 구체적으로 받을 것
	TArray<FIntVector2> FreeMovableWalkingPoints;
	GetTargetZoneMovablePoints(FreeMovableWalkingPoints, aSearchZoneType, aNotMovablePoints);
	
	
	// Search
	TQueue<FIntVector2> Queue;
	TMap<FIntVector2, FIntVector2> VisitedPointToPreviousPoints;
	aOutPath.Empty();
	
	Queue.Enqueue(aStartPosition);

	VisitedPointToPreviousPoints.Emplace(aStartPosition, FIntVector2::ZeroValue);

	bool bSucceed = false;
	FIntVector2 SucceedTarget = FIntVector2::ZeroValue;
	
	while(!bSucceed && !Queue.IsEmpty())
	{
		FIntVector2 TestPoint;
		
		if (Queue.Dequeue(TestPoint))
		{
			for (const FIntVector2& TestAddedPoint : TestAddedPoints)
			{
				FIntVector2 EnqueuePoint = TestPoint + TestAddedPoint;
				
				if (FreeMovableWalkingPoints.Contains(EnqueuePoint))
				{
					if (!VisitedPointToPreviousPoints.Contains(EnqueuePoint))
					{
						Queue.Enqueue(EnqueuePoint);
						VisitedPointToPreviousPoints.Emplace(EnqueuePoint, TestPoint);

						if (aTargetPositions.Contains(EnqueuePoint))
						{
							bSucceed = true;
							SucceedTarget = EnqueuePoint;
							break;
						}
					}
				}
			}	
		}

		if (bSucceed)
		{
			break;
		}
	}

	if (bSucceed)
	{
		TArray<FIntVector2> PathBackwards;
		PathBackwards.Empty();

		FIntVector2 PreviousPoint = SucceedTarget;
		PathBackwards.Emplace(PreviousPoint);

		while (PreviousPoint != aStartPosition)
		{
			FIntVector2* pPreviousPoint = VisitedPointToPreviousPoints.Find(PreviousPoint);
			if (pPreviousPoint == nullptr)
			{
				MS_ENSURE(false);
				return;
			}
			
			PreviousPoint = *pPreviousPoint;
			PathBackwards.Emplace(PreviousPoint);
		}

		for (int32 i = PathBackwards.Num() - 1; i >= 0; --i)
		{
			aOutPath.Emplace(PathBackwards[i]);
		}
	}
}

void UMS_PathFinder::SearchAStar(TArray<FIntVector2>& aOutPath, EMS_ZoneType aSearchZoneType, const FIntVector2& aStartPosition,
	const TArray<FIntVector2>& aTargetPositions, const TArray<FIntVector2>& aNotMovablePoints /*= {}*/) const
{
	// Target
	FIntVector2 HeuristicTargetPosition = SelectHeuristicTarget(aTargetPositions);
	
	// 다른 타입의 존일때 Gate까지만 계산해서 계산량을 줄임
	// 따라서 인자로 같은 존의 값이 넘어오게 됨
	// ToDo : 같은 존 타입 사이에 Gate를 두게 됐을때 aSearchZoneType 인자를 더 구체적으로 받을 것
	TArray<FIntVector2> NotMovablePoints = aNotMovablePoints;
	NotMovablePoints.Remove(aStartPosition);
	
	TArray<FIntVector2> FreeMovableWalkingPoints;
	GetTargetZoneMovablePoints(FreeMovableWalkingPoints, aSearchZoneType, NotMovablePoints);

	TArray<int32> HeuristicCosts;
	GetHeuristicCosts(FreeMovableWalkingPoints, aStartPosition, HeuristicTargetPosition, HeuristicCosts);
	
	// Search
	TMS_PriorityQueue<FIntVector2> PriorityQueue;
	
	TMap<FIntVector2, FIntVector2> VisitedPointToPreviousPoints;
	aOutPath.Empty();

	int32 StartPositionIndex = FreeMovableWalkingPoints.Find(aStartPosition);
	if (StartPositionIndex == INDEX_NONE)
	{
		return;
	}
	
	PriorityQueue.Enqueue(aStartPosition, HeuristicCosts[StartPositionIndex]);

	VisitedPointToPreviousPoints.Emplace(aStartPosition, FIntVector2::ZeroValue);

	bool bSucceed = false;
	FIntVector2 SucceedTarget = FIntVector2::ZeroValue;

	if (aTargetPositions.Contains(aStartPosition))
	{
		bSucceed = true;
		SucceedTarget = aStartPosition;
	}
	
	while(!bSucceed && !PriorityQueue.IsEmpty())
	{
		FIntVector2 TestPoint;
		
		if (PriorityQueue.Dequeue(TestPoint))
		{
			for (const FIntVector2& TestAddedPoint : TestAddedPoints)
			{
				FIntVector2 EnqueuePoint = TestPoint + TestAddedPoint;

				int32 EnqueuePointIndex = FreeMovableWalkingPoints.Find(EnqueuePoint);
				if (EnqueuePointIndex != INDEX_NONE)
				{
					if (!VisitedPointToPreviousPoints.Contains(EnqueuePoint))
					{
						PriorityQueue.Enqueue(EnqueuePoint, HeuristicCosts[StartPositionIndex]);
						VisitedPointToPreviousPoints.Emplace(EnqueuePoint, TestPoint);

						if (aTargetPositions.Contains(EnqueuePoint))
						{
							bSucceed = true;
							SucceedTarget = EnqueuePoint;
							break;
						}
					}
				}
			}
		}
		
		if (bSucceed)
		{
			break;
		}
	}

	if (bSucceed)
	{
		TArray<FIntVector2> PathBackwards;
		PathBackwards.Empty();

		FIntVector2 PreviousPoint = SucceedTarget;
		PathBackwards.Emplace(PreviousPoint);

		while (PreviousPoint != aStartPosition)
		{
			FIntVector2* pPreviousPoint = VisitedPointToPreviousPoints.Find(PreviousPoint);
			if (pPreviousPoint == nullptr)
			{
				MS_ENSURE(false);
				return;
			}
			
			PreviousPoint = *pPreviousPoint;
			PathBackwards.Emplace(PreviousPoint);
		}

		for (int32 i = PathBackwards.Num() - 1; i >= 0; --i)
		{
			aOutPath.Emplace(PathBackwards[i]);
		}
	}
}

void UMS_PathFinder::GetTargetZoneMovablePoints(TArray<FIntVector2>& aOutPoints, EMS_ZoneType aSearchZoneType,
	const TArray<FIntVector2>& aNotMovablePoints) const
{
	switch (aSearchZoneType)
	{
	case EMS_ZoneType::Display :
		{
			aOutPoints = DisplayFreeMovableWalkingPoints;
			break;
		}

	case EMS_ZoneType::Shelf :
		{
			aOutPoints = ShelfFreeMovableWalkingPoints;
			break;
		}

	case EMS_ZoneType::Pallet :
		{
			aOutPoints = PalletFreeMovableWalkingPoints;
			break;
		}

	case EMS_ZoneType::Outside :
		{
			aOutPoints = OutsideFreeMovableWalkingPoints;
			break;
		}
		
	default:
		{
			MS_ENSURE(false);
			return;
		}
	}

	// NotMovablePoint
	for (const FIntVector2& NotMovablePoint : aNotMovablePoints)
	{
		if (aOutPoints.Contains(NotMovablePoint))
		{
			aOutPoints.RemoveSingle(NotMovablePoint);
		}
	}
}

FIntVector2 UMS_PathFinder::SelectHeuristicTarget(const TArray<FIntVector2>& aTargetPositions) const
{
	int32 MinDistance = INT_MAX;
	FIntVector2 HeuristicTargetPosition;
	
	for (const FIntVector2& TargetPosition : aTargetPositions)
	{
		int32 TargetDistance = TargetPosition.X + TargetPosition.Y;
		if (TargetDistance < MinDistance)
		{
			HeuristicTargetPosition = TargetPosition;
			MinDistance = TargetDistance;
		}
	}

	return HeuristicTargetPosition;
}

void UMS_PathFinder::GetHeuristicCosts(const TArray<FIntVector2>& aPoints, const FIntVector2& aStartPosition, const FIntVector2& aHeuristicTarget,
	TArray<int32>& aOutCosts) const
{
	for (const FIntVector2& Point : aPoints)
	{
		aOutCosts.Emplace(FMath::Abs(Point.X - aStartPosition.X) + FMath::Abs(Point.Y - aStartPosition.Y) + FMath::Abs(aHeuristicTarget.X - Point.X) + FMath::Abs(aHeuristicTarget.Y - Point.Y));
	}
}

bool UMS_PathFinder::GetRandomPosition(EMS_ZoneType aZoneType, FIntVector2& aOutPosition) const
{
	TArray<FIntVector2> FreeMovableWalkingPoints;
	switch (aZoneType)
	{
	case EMS_ZoneType::Display :
		{
			if (DisplayFreeMovableWalkingPoints.Num() > 0)
			{
				int32 Random = FMath::RandRange(0, DisplayFreeMovableWalkingPoints.Num() - 1);
				aOutPosition = DisplayFreeMovableWalkingPoints[Random];
				return true;
			}
			break;
		}

	case EMS_ZoneType::Shelf :
		{
			if (ShelfFreeMovableWalkingPoints.Num() > 0)
			{
				int32 Random = FMath::RandRange(0, ShelfFreeMovableWalkingPoints.Num() - 1);
				aOutPosition = ShelfFreeMovableWalkingPoints[Random];
				return true;
			}
			break;
		}

	case EMS_ZoneType::Pallet :
		{
			if (PalletFreeMovableWalkingPoints.Num() > 0)
			{
				int32 Random = FMath::RandRange(0, PalletFreeMovableWalkingPoints.Num() - 1);
				aOutPosition = PalletFreeMovableWalkingPoints[Random];
				return true;
			}
			break;
		}

	case EMS_ZoneType::Outside :
		{
			if (OutsideFreeMovableWalkingPoints.Num() > 0)
			{
				int32 Random = FMath::RandRange(0, OutsideFreeMovableWalkingPoints.Num() - 1);
				aOutPosition = OutsideFreeMovableWalkingPoints[Random];
				return true;
			}
			break;
		}
		
	default:
		{
			MS_ENSURE(false);
			return false;
		}
	}
	
	return false;
}
