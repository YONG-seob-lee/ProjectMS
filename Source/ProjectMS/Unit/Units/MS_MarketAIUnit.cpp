// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketAIUnit.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MS_CustomerAIUnit.h"
#include "MS_FurnitureUnit.h"
#include "MS_StaffAIUnit.h"
#include "Character/MS_CharacterBase.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Prop/Furniture/MS_Furniture.h"


bool UMS_MarketAIUnit::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	if (Super::CreateUnitActor(aPosition, aRotator))
	{
		AMS_MarketAICharacter* AICharacter = Cast<AMS_MarketAICharacter>(GetCharacter());
		MS_ENSURE(AICharacter);

		AICharacter->OnReachPathLocationDelegate.BindUObject(this, &UMS_MarketAIUnit::OnReachPathLocation);

		return true;
	}
	
	return false;
}

bool UMS_MarketAIUnit::SetUnitCharacter(TObjectPtr<AMS_CharacterBase> aUnitCharacter, bool bForced)
{
	if (Super::SetUnitCharacter(aUnitCharacter, bForced))
	{
		AMS_MarketAICharacter* AICharacter = Cast<AMS_MarketAICharacter>(GetCharacter());
		MS_ENSURE(AICharacter);

		AICharacter->OnReachPathLocationDelegate.BindUObject(this, &UMS_MarketAIUnit::OnReachPathLocation);

		return true;
	}
	
	return false;
}

FIntVector2 UMS_MarketAIUnit::GetActorGridPosition() const
{
	if (GetCharacter())
	{
		FVector CharacterLocation = GetCharacter()->GetActorLocation();
		return FMS_GridData::ConvertLocationToGridPosition(CharacterLocation);
	}

	MS_ENSURE(false);
	return FIntVector2::ZeroValue;
}

TArray<FIntVector2> UMS_MarketAIUnit::GetFullActorGridPositions() const
{
	TArray<FIntVector2> Positions = {};

	if (GetCharacter())
	{
		FVector CharacterLocation = GetCharacter()->GetActorLocation();
		
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(-60.f, -60.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(0.f, -60.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(60.f, -60.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(-60.f, 0.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(60.f, 0.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(-60.f, 60.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(0.f, 60.f, 0.f)));
		Positions.AddUnique(FMS_GridData::ConvertLocationToGridPosition(CharacterLocation - FVector(60.f, 60.f, 0.f)));
		
		return Positions;
	}

	MS_ENSURE(false);
	return Positions;
}

FVector UMS_MarketAIUnit::GetActorLocation() const
{
	if (GetCharacter())
	{
		return GetCharacter()->GetActorLocation();
	}

	return FVector::ZeroVector;
}

FRotator UMS_MarketAIUnit::GetActorRotator() const
{
	if (GetCharacter())
	{
		return GetCharacter()->GetActorRotation();
	}

	return FRotator::ZeroRotator;
}

void UMS_MarketAIUnit::ResetPath()
{
	AMS_MarketAICharacter* MarketAICharacter = Cast<AMS_MarketAICharacter>(GetCharacter());
	if (IsValid(MarketAICharacter))
	{
		MarketAICharacter->SetWalkingDirectionAndPathLocation(EMS_Direction::None, FVector2D::ZeroVector, true);
	}
	
	CacheTargetPositions.Empty();
	CachePath.Empty();

	RemainStopTime = 0.f;
}

EBTNodeResult::Type UMS_MarketAIUnit::UpdateActorLocationByPath(float aDeltaSeconds)
{
	AMS_MarketAICharacter* MarketAICharacter = Cast<AMS_MarketAICharacter>(GetCharacter());
	if (!IsValid(MarketAICharacter))
	{
		return EBTNodeResult::Failed;
	}
	
	if (CachePath.Num() == 0)
	{
		return EBTNodeResult::Succeeded;
	}

	if (RemainStopTime > 0.f)
	{
		RemainStopTime -= aDeltaSeconds;

		if (RemainStopTime <= 0.f)
		{
			RemainStopTime = 0.f;
		}
		
		else
		{
			MarketAICharacter->SetWalkingDirectionAndPathLocation(EMS_Direction::None, FVector2D::Zero(), true);
			return EBTNodeResult::InProgress;
		}
	}
	
	const FVector2D CurrentLocationXY = FVector2D(GetActorLocation().X, GetActorLocation().Y);
	const FRotator CurrentRotator = GetActorRotator();
	
	if (CachePath.Num() == 1)
	{
		FVector2D PathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[0],
			IsGridSizeXOdd(), IsGridSizeYOdd());
		
		EMS_Direction Direction = UMS_MathUtility::GetDirection(CurrentLocationXY, PathLocationXY);
		
		if (Direction == EMS_Direction::None)
		{
			// 도착지에 PropSpace가 있는 경우
			TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
			if (FurnitureUnit != nullptr)
			{
				TWeakObjectPtr<UMS_PropSpaceComponent> PropSpace = GetInteractionPropSpaceComponent();
				if (PropSpace != nullptr)
				{
					FRotator FurnitureRotator = FurnitureUnit->GetActorRotator();
					EMS_Rotation FurnitureRotation = UMS_MathUtility::ConvertRotation(FurnitureRotator.Yaw);
				
					EMS_Rotation PropSpaceRotation = PropSpace->GetCharacterRotation();
				
					EMS_Rotation TargetRotation = UMS_MathUtility::Rotate(FurnitureRotation, PropSpaceRotation);
					EMS_Direction TargetDirection = UMS_MathUtility::ConvertRotationToDirection(TargetRotation);
				
					if (FMath::IsNearlyEqual(CurrentLocationXY.X, PathLocationXY.X, MS_ERROR_TOLERANCE) && FMath::IsNearlyEqual(CurrentLocationXY.Y, PathLocationXY.Y, MS_ERROR_TOLERANCE))
					{
						float CurrentRotatorYaw = CurrentRotator.Yaw;
						if (CurrentRotatorYaw < 0.f)
						{
							CurrentRotatorYaw += 360.f;
						}
						
						if (FMath::IsNearlyEqual(CurrentRotatorYaw, UMS_MathUtility::ConvertRotation(TargetRotation), MS_ERROR_TOLERANCE))
						{
							// 이미 도착지에 도착한 것
							CachePath.RemoveAt(0);
							MarketAICharacter->SetWalkingDirectionAndPathLocation(EMS_Direction::None, PathLocationXY, true);
							return EBTNodeResult::Succeeded;
						}
					}
				
					MarketAICharacter->SetWalkingDirectionAndPathLocation(TargetDirection, PathLocationXY, true);
					return EBTNodeResult::InProgress;
				}
			}
			
			// 도착지에 PropSpace가 없는 경우
			CachePath.RemoveAt(0);
			MarketAICharacter->SetWalkingDirectionAndPathLocation(EMS_Direction::None, PathLocationXY, true);
			return EBTNodeResult::Succeeded;
		}
		
		MarketAICharacter->SetWalkingDirectionAndPathLocation(Direction, PathLocationXY, true);
		return EBTNodeResult::InProgress;
	}

	else
	{
		FVector2D PathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[0],
			IsGridSizeXOdd(), IsGridSizeYOdd());

		FVector2D NextPathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[1],
			IsGridSizeXOdd(), IsGridSizeYOdd());

		EMS_Direction Direction = UMS_MathUtility::GetDirection(CurrentLocationXY, PathLocationXY);
		EMS_Direction NextDirection = UMS_MathUtility::GetDirection(PathLocationXY, NextPathLocationXY);
		
		if (Direction == EMS_Direction::None)
		{
			// 이동을 시작할 때 
			CachePath.RemoveAt(0);
			MarketAICharacter->SetRotationByWalkingDirection(NextDirection);
			
			// ===== OnReachPathLocationDelegate를 통해 이미 삭제 된 부분 ===== //
			// 방향 바꾸는 타이밍
			// CachePath.RemoveAt(0);
			// MarketAICharacter->SetWalkingDirection(EMS_Direction::None, FVector2D::ZeroVector, true);

			// 재귀를 이용해 한 틱 멈추거나 코드가 복잡해지지 않고 다시 실행
			//return UpdateActorLocationByPath();
			// ========== //
		}
		
		if (Direction == NextDirection)
		{
			// 딱 맞게 서지 말고 자연스럽게 넘어가면서 이동
			MarketAICharacter->SetWalkingDirectionAndPathLocation(Direction, PathLocationXY, false);
			return EBTNodeResult::InProgress;
		}

		// 방향이 바뀌므로 딱 맞게 설 것
		MarketAICharacter->SetWalkingDirectionAndPathLocation(Direction, PathLocationXY, true);
		return EBTNodeResult::InProgress;
	}
}

void UMS_MarketAIUnit::OnReachPathLocation(const FVector2D& aReachedLocation)
{
	if (CachePath.Num() <= 1)	// Num == 1 일때는 아직 방향 회전이 남아있을 수 있어 UpdateActorLocationByPath()에서 삭제
	{
		return;
	}
	
	FVector2D PathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[0],
		IsGridSizeXOdd(), IsGridSizeYOdd());
	
	// MS_ENSURE(aReachedLocation == PathLocationXY);
	CachePath.RemoveAt(0);
}

TWeakObjectPtr<UMS_FurnitureUnit> UMS_MarketAIUnit::GetInteractableFurnitureUnit() const
{
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		TWeakObjectPtr<AActor> Actor = LevelScriptActor->GetGridObject(GetActorGridPosition());

		if (Actor != nullptr)
		{
			if (AMS_Furniture* FurnitureActor = Cast<AMS_Furniture>(Actor.Get()))
			{
				return Cast<UMS_FurnitureUnit>(FurnitureActor->GetOwnerUnitBase());
			}
		}
	}
	
	return nullptr;
}

TWeakObjectPtr<UMS_PropSpaceComponent> UMS_MarketAIUnit::GetInteractionPropSpaceComponent() const
{
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		return LevelScriptActor->GetGridPropSpace(GetActorGridPosition());
	}
	
	return nullptr;
}

bool UMS_MarketAIUnit::GetPathPoint(int32 aIndex, FIntVector2& OutPathPoint) const
{
	if (CachePath.IsValidIndex(aIndex))
	{
		OutPathPoint = CachePath[aIndex];
		return true;
	}

	return false;
}

void UMS_MarketAIUnit::SearchPathToTarget(TArray<FIntVector2>& aOutPath, const FIntVector2& aStartPosition,
	const TArray<FIntVector2>& aTargetPositions, const TArray<FIntVector2>& NotMovablePoints) const
{
	TObjectPtr<UMS_ModeStateBase> ModeState = gModeMng.GetCurrentModeState();
	if (ModeState == nullptr)
	{
		return;
	}
	
	ModeState->SearchPathToTarget(aOutPath, GetActorGridPosition(), GetTargetPositions(), NotMovablePoints);
}

void UMS_MarketAIUnit::NotifyActorBeginOverlap(UMS_MarketAIUnit* aOtherUnit)
{
	if (!CachePath.IsValidIndex(0))
	{
		return;
	}
	
	// UnitDirection
	const FVector2D UnitLocationXY = FVector2D(GetActorLocation().X, GetActorLocation().Y);
	
	FVector2D PathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[0],
			IsGridSizeXOdd(), IsGridSizeYOdd());
		
	EMS_Direction UnitDirection = UMS_MathUtility::GetDirection(UnitLocationXY, PathLocationXY);

	// OtherUnitDirection
	EMS_Direction OtherUnitDirection = EMS_Direction::None;

	const FVector2D OtherUnitLocationXY = FVector2D(aOtherUnit->GetActorLocation().X, aOtherUnit->GetActorLocation().Y);

	FIntVector2 FirstOtherUnitPathPoint;
	if (aOtherUnit->GetPathPoint(0, FirstOtherUnitPathPoint))
	{
		FVector2D OtherPathLocationXY = FMS_GridData::ConvertGridPositionToLocation(FirstOtherUnitPathPoint,
				aOtherUnit->IsGridSizeXOdd(), aOtherUnit->IsGridSizeYOdd());
	
		OtherUnitDirection = UMS_MathUtility::GetDirection(OtherUnitLocationXY, OtherPathLocationXY);
	}

	// 행동
	if (UnitDirection == EMS_Direction::None /*|| IsStopped()*/)
	{
		return;
	}

	if (OtherUnitDirection == EMS_Direction::None /*|| IsStopped()*/)
	{
		FIntVector2 OtherUnitGridPosition = aOtherUnit->GetActorGridPosition();
		if (aOtherUnit->GetActorGridPosition() == CachePath.Last())
		{
			StopMove(5.f);
		}
		else
		{
			TArray<FIntVector2> NewPath;
			SearchPathToTarget(NewPath, GetActorGridPosition(), CacheTargetPositions, aOtherUnit->GetFullActorGridPositions());

			if (NewPath.Num() > 1)
			{
				CachePath = NewPath;
			}
		}
		
		return;
	}

	if (UnitDirection == OtherUnitDirection)
	{
		FVector DirectionVector = UMS_MathUtility::ConvertDirectionToVector(UnitDirection);
		FVector LocationDiff = aOtherUnit->GetActorLocation() - GetActorLocation();

		float DotProduct = DirectionVector.X * LocationDiff.X + DirectionVector.Y * LocationDiff.Y;

		if (DotProduct > 0.f) // UnitDirection 기준으로 내가 더 뒤쪽에 있음
		{
			StopMove(5.f);
		}
	}
	else
	{
		if (IsA(UMS_CustomerAIUnit::StaticClass()) && aOtherUnit->IsA(UMS_StaffAIUnit::StaticClass()))
		{
			return;
		}
		
		if ((IsA(UMS_StaffAIUnit::StaticClass()) && aOtherUnit->IsA(UMS_CustomerAIUnit::StaticClass()))
			|| UnitHandle > aOtherUnit->GetUnitHandle())
		{
			TArray<FIntVector2> NewPath;
			SearchPathToTarget(NewPath, GetActorGridPosition(), CacheTargetPositions, aOtherUnit->GetFullActorGridPositions());

			if (NewPath.Num() > 1)
			{
				CachePath = NewPath;
			}
			else
			{
				StopMove(2.f);
			}
		}
	}
}

void UMS_MarketAIUnit::StopMove(float aTime)
{
	RemainStopTime = aTime;
}

FMS_SlotData UMS_MarketAIUnit::GetSlotData(int32 aSlotId) const
{
	if (SlotDatas.IsValidIndex(aSlotId))
	{
		return SlotDatas[aSlotId];
	}
	
	return FMS_SlotData();
}

void UMS_MarketAIUnit::ResetSlotDatas()
{
	for (FMS_SlotData& SlotData : SlotDatas)
	{
		SlotData = FMS_SlotData();
	}
	
	OnChangeCurrentSlotDatas();
	gItemMng.UpdateNotPlacedItemsToPalletItems();
}

bool UMS_MarketAIUnit::AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount)
{
	if (!SlotDatas.IsValidIndex(aSlotId))
	{
		MS_ENSURE(false);
		return false;
	}
	
	if (SlotDatas[aSlotId].CurrentItemTableId != aItemId)
	{
		if (SlotDatas[aSlotId].CurrentItemCount == 0)
		{
			SlotDatas[aSlotId].CurrentItemTableId = aItemId;
		}
		else
		{
			MS_ENSURE(false);
			return false;
		}
	}
	
	SlotDatas[aSlotId].CurrentItemCount += aCount;
	
	OnChangeCurrentSlotDatas();
	return true;
}

bool UMS_MarketAIUnit::SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount)
{
	if (!SlotDatas.IsValidIndex(aSlotId))
	{
		MS_ENSURE(false);
		return false;
	}

	if (SlotDatas[aSlotId].CurrentItemTableId != aItemId)
	{
		MS_ENSURE(false);
		return false;
	}

	if (SlotDatas[aSlotId].CurrentItemCount < aCount)
	{
		MS_ENSURE(false);
		return false;
	}
		
	SlotDatas[aSlotId].CurrentItemCount -= aCount;

	if (SlotDatas[aSlotId].CurrentItemCount == 0)
	{
		SlotDatas[aSlotId].CurrentItemTableId = INDEX_NONE;
	}
	
	OnChangeCurrentSlotDatas();
	return true;
}

void UMS_MarketAIUnit::EventChatting(EMS_ChattingType ChattingType) const
{
	if(const TObjectPtr<AMS_MarketAICharacter> Customer = Cast<AMS_MarketAICharacter>(GetCharacter()))
	{
		Customer->ShowChatting(ChattingType);
	}
}

void UMS_MarketAIUnit::EventChattingImage(EMS_SpeechImageType SpeechImageType) const
{
	if(const TObjectPtr<AMS_MarketAICharacter> Customer = Cast<AMS_MarketAICharacter>(GetCharacter()))
	{
		Customer->ShowImage(SpeechImageType);
	}
}

bool UMS_MarketAIUnit::IsChatBefore() const
{
	if(const TObjectPtr<AMS_MarketAICharacter> Customer = Cast<AMS_MarketAICharacter>(GetCharacter()))
	{
		return Customer->IsChattingBefore();
	}

	return false;
}

void UMS_MarketAIUnit::ResetChatting() const
{
	if(const TObjectPtr<AMS_MarketAICharacter> Customer = Cast<AMS_MarketAICharacter>(GetCharacter()))
	{
		Customer->ResetChatting();
	}
}

void UMS_MarketAIUnit::OnChangeCurrentSlotDatas()
{
	AMS_MarketAICharacter* MarketAICharacter = Cast<AMS_MarketAICharacter>(GetCharacter());
	MS_ENSURE (IsValid(MarketAICharacter));
	
	MarketAICharacter->OnChangeCurrentSlotDatas(SlotDatas);
}
