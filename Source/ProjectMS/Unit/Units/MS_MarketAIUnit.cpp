// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketAIUnit.h"

#include "Character/MS_CharacterBase.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "ContentsUtilities/MS_LevelDefine.h"


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

FVector UMS_MarketAIUnit::GetActorLocation() const
{
	if (GetCharacter())
	{
		return GetCharacter()->GetActorLocation();
	}

	return FVector::ZeroVector;
}

EBTNodeResult::Type UMS_MarketAIUnit::UpdateActorLocationByPath()
{
	AMS_MarketAICharacter* MarketAICharacter = Cast<AMS_MarketAICharacter>(GetCharacter());
	if (!IsValid(MarketAICharacter))
	{
		return EBTNodeResult::Failed;
	}
	
	if (CachePath.Num() == 0)
	{
		MS_ENSURE(false);
		return EBTNodeResult::Failed;
	}

	const FVector2D CurrentLocationXY = FVector2D(GetActorLocation().X, GetActorLocation().Y);
	
	if (CachePath.Num() == 1)
	{
		FVector2D PathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[0],
			!IsGridSizeXOdd(), !IsGridSizeYOdd());

		EMS_Direction Direction = UMS_MathUtility::GetDirection(CurrentLocationXY, PathLocationXY);
		if (Direction == EMS_Direction::None)
		{
			// 도착지에 도착한 것
			CachePath.RemoveAt(0);
			return EBTNodeResult::Succeeded;
		}

		MarketAICharacter->SetWalkingDirection(Direction, PathLocationXY, true);
		return EBTNodeResult::InProgress;
	}

	else
	{
		FVector2D PathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[0],
			!IsGridSizeXOdd(), !IsGridSizeYOdd());

		FVector2D NextPathLocationXY = FMS_GridData::ConvertGridPositionToLocation(CachePath[1],
	!IsGridSizeXOdd(), !IsGridSizeYOdd());

		EMS_Direction Direction = UMS_MathUtility::GetDirection(CurrentLocationXY, PathLocationXY);
		EMS_Direction NextDirection = UMS_MathUtility::GetDirection(PathLocationXY, NextPathLocationXY);
		
		if (Direction == EMS_Direction::None)
		{
			// 방향 바꾸는 타이밍
			// 멈추고 다음 틱부터 방향 바꿔서 이동
			CachePath.RemoveAt(0);
			MarketAICharacter->SetWalkingDirection(EMS_Direction::None, FVector2D::ZeroVector, true);
			return EBTNodeResult::InProgress;
		}

		if (Direction == NextDirection)
		{
			// 딱 맞게 서지 말고 자연스럽게 넘어가면서 이동
			MarketAICharacter->SetWalkingDirection(Direction, PathLocationXY, false);
			return EBTNodeResult::InProgress;
		}

		// 방향이 바뀌므로 딱 맞게 설 것
		MarketAICharacter->SetWalkingDirection(Direction, PathLocationXY, true);
		return EBTNodeResult::InProgress;
	}
}
