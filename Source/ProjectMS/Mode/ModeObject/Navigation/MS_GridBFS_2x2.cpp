#include "MS_GridBFS_2x2.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "Manager_Client/MS_SceneManager.h"


UMS_GridBFS_2x2::UMS_GridBFS_2x2()
{
}

void UMS_GridBFS_2x2::CollectMovingPoints()
{
	CollectDisplayMovingPoints();
	CollectShelfMovingPoints();
	CollectPalletMovingPoints();
}

void UMS_GridBFS_2x2::CollectDisplayMovingPoints()
{
	DisplayFreeMovableGridPositions.Empty();
	DisplayFreeMovableWalkingPoints.Empty();
	
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		LevelScriptActor->GetFreeMovableGridPositions(DisplayFreeMovableGridPositions, EMS_ZoneType::Display);

		// O 그리드를 좌상단 좌표 기준으로 3방향 그리드가 있는지 확인
		// XX
		// XO
		for (const FIntVector2& GridPosition : DisplayFreeMovableGridPositions)
		{
			if (!DisplayFreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, -1)))
			{
				continue;
			}

			if (!DisplayFreeMovableGridPositions.Contains(GridPosition + FIntVector2(0, -1)))
			{
				continue;
			}

			if (!DisplayFreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, 0)))
			{
				continue;
			}

			DisplayFreeMovableWalkingPoints.Add(GridPosition);
		}
	}
}

void UMS_GridBFS_2x2::CollectShelfMovingPoints()
{
	ShelfFreeMovableGridPositions.Empty();
	ShelfFreeMovableWalkingPoints.Empty();
	
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		LevelScriptActor->GetFreeMovableGridPositions(ShelfFreeMovableGridPositions, EMS_ZoneType::Shelf);

		// O 그리드를 좌상단 좌표 기준으로 3방향 그리드가 있는지 확인
		// XX
		// XO
		for (const FIntVector2& GridPosition : ShelfFreeMovableGridPositions)
		{
			if (!ShelfFreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, -1)))
			{
				continue;
			}

			if (!ShelfFreeMovableGridPositions.Contains(GridPosition + FIntVector2(0, -1)))
			{
				continue;
			}

			if (!ShelfFreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, 0)))
			{
				continue;
			}

			ShelfFreeMovableWalkingPoints.Add(GridPosition);
		}
	}
}

void UMS_GridBFS_2x2::CollectPalletMovingPoints()
{
	PalletFreeMovableGridPositions.Empty();
	PalletFreeMovableWalkingPoints.Empty();
	
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		LevelScriptActor->GetFreeMovableGridPositions(PalletFreeMovableGridPositions, EMS_ZoneType::Pallet);

		// O 그리드를 좌상단 좌표 기준으로 3방향 그리드가 있는지 확인
		// XX
		// XO
		for (const FIntVector2& GridPosition : PalletFreeMovableGridPositions)
		{
			if (!PalletFreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, -1)))
			{
				continue;
			}

			if (!PalletFreeMovableGridPositions.Contains(GridPosition + FIntVector2(0, -1)))
			{
				continue;
			}

			if (!PalletFreeMovableGridPositions.Contains(GridPosition + FIntVector2(-1, 0)))
			{
				continue;
			}

			PalletFreeMovableWalkingPoints.Add(GridPosition);
		}
	}
}

void UMS_GridBFS_2x2::Search(TArray<FIntVector2>& aOutPath, const FIntVector2& aStartPoint,
	const TArray<FIntVector2>& aTargetPoints) const
{
	TQueue<FIntVector2> Queue;
	TMap<FIntVector2, FIntVector2> VisitedPointToPreviousPoints;
	aOutPath.Empty();
	
	Queue.Enqueue(aStartPoint);

	VisitedPointToPreviousPoints.Emplace(aStartPoint, FIntVector2::ZeroValue);

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
				
				if (ShelfFreeMovableWalkingPoints.Contains(EnqueuePoint))
				{
					if (!VisitedPointToPreviousPoints.Contains(EnqueuePoint))
					{
						Queue.Enqueue(EnqueuePoint);
						VisitedPointToPreviousPoints.Emplace(EnqueuePoint, TestPoint);
					}
				}

				if (aTargetPoints.Contains(EnqueuePoint))
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

		while (PreviousPoint == aStartPoint)
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
