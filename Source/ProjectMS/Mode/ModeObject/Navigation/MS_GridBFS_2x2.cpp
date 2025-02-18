#include "MS_GridBFS_2x2.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "Manager_Client/MS_SceneManager.h"


UMS_GridBFS_2x2::UMS_GridBFS_2x2()
{
}

void UMS_GridBFS_2x2::CollectAllZoneTypeMovingPoints()
{
	CollectMovingPoints(EMS_ZoneType::Display);
	CollectMovingPoints(EMS_ZoneType::Shelf);
	CollectMovingPoints(EMS_ZoneType::Pallet);
}

void UMS_GridBFS_2x2::CollectMovingPoints(EMS_ZoneType aCollectZoneType)
{
	TArray<FIntVector2> FreeMovableGridPositions;
	FreeMovableGridPositions.Empty();
	PalletFreeMovableWalkingPoints.Empty();
	
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

			default:
				{
					MS_ENSURE(false);
					return;
				}
			}
		}
	}
}

void UMS_GridBFS_2x2::Search(TArray<FIntVector2>& aOutPath, EMS_ZoneType aSearchZoneType, const FIntVector2& aStartPosition,
	const TArray<FIntVector2>& aTargetPositions) const
{
	// 다른 타입의 존일때 Gate까지만 계산해서 계산량을 줄임
	// ToDo : 같은 존 타입 사이에 Gate를 두게 됐을때 aSearchZoneType 인자를 더 구체적으로 받을 것
	TArray<FIntVector2> FreeMovableWalkingPoints;
	switch (aSearchZoneType)
	{
	case EMS_ZoneType::Display :
		{
			FreeMovableWalkingPoints = DisplayFreeMovableWalkingPoints;
			break;
		}

	case EMS_ZoneType::Shelf :
		{
			FreeMovableWalkingPoints = ShelfFreeMovableWalkingPoints;
			break;
		}

	case EMS_ZoneType::Pallet :
		{
			FreeMovableWalkingPoints = PalletFreeMovableWalkingPoints;
			break;
		}

	default:
		{
			MS_ENSURE(false);
			return;
		}
	}

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
					}
				}

				if (aTargetPositions.Contains(EnqueuePoint))
				{
					bSucceed = true;
					SucceedTarget = EnqueuePoint;
					break;
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
