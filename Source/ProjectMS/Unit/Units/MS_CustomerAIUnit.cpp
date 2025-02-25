// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerAIUnit.h"

#include "MS_ActorUnitBase.h"
#include "UtilityFunctions.h"
#include "Character/MS_CharacterBase.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Prop/Spline/MS_CustomerSplineActor.h"
#include "Table/Caches/MS_CustomerCacheTable.h"

void UMS_CustomerAIUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	const TObjectPtr<UMS_CustomerCacheTable> CustomerTable = Cast<UMS_CustomerCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Customer));
	MS_ENSURE(CustomerTable);

	CustomerTable->MakeNewCustomerData(CustomerData);
}

void UMS_CustomerAIUnit::Finalize()
{
	Super::Finalize();
}

void UMS_CustomerAIUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_CustomerAIUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_CustomerAIUnit::FindNearestSpline()
{
	TArray<TObjectPtr<UMS_UnitBase>> DuckSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::CustomerSpline, DuckSplineUnits);

	float DistanceMin = 0.f;
	TObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
	for(const auto& SplineUnit : DuckSplineUnits)
	{
		if(const TObjectPtr<UMS_ActorUnitBase> SplineActorUnit = Cast<UMS_ActorUnitBase>(SplineUnit))
		{
			const float Distance = FVector::Distance(GetActorLocation(), SplineActorUnit->GetUnitPosition());
			if(DistanceMin == 0.f || DistanceMin > Distance)
			{
				DistanceMin = Distance;
				NearestSplineUnit = SplineActorUnit;
			}
		}
	}

	if(!NearestSplineUnit)
	{
		return false;
	}

	if(const TObjectPtr<AMS_CustomerSplineActor> SplineActor = Cast<AMS_CustomerSplineActor>(NearestSplineUnit->GetActor()))
	{
		CustomerSplineActor = SplineActor;
		return true;
	}

	return false;
}

bool UMS_CustomerAIUnit::ReachSplineEndPoint() const
{
	if(CustomerSplineActor.IsValid() == false)
	{
		return false;
	}
	const FVector ActorLocation = GetActorLocation();
	const FVector SplineEndPoint = CustomerSplineActor->GetEndPoint();
	if(FVector::Distance(ActorLocation, SplineEndPoint) < 10.f)
	{
		return true;
	}

	return false;
}

void UMS_CustomerAIUnit::GoingToMarket() const
{
	if(CustomerSplineActor.IsValid())
	{
		const FVector CurrentVehicleLocation = GetActorLocation();
		const FVector TangentLocation = CustomerSplineActor->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
		FRotator MoveNextRotation = TangentLocation.Rotation();
		MoveNextRotation.Yaw -= 90.f;
		const FVector ClosetLocation = CustomerSplineActor->FindLocationClosestToWorldLocation(CurrentVehicleLocation);
		if(const TObjectPtr<AMS_CharacterBase> CustomerCharacter = GetCharacter())
		{
			CustomerCharacter->SetActorLocation(ClosetLocation + TangentLocation.GetSafeNormal() * 5.f);
			CustomerCharacter->SetActorRotation(MoveNextRotation);
		}
	}
}

int32 UMS_CustomerAIUnit::GetBlueprintPathId() const
{
	return CustomerData.GetCharacterBPPathFile();
}

UClass* UMS_CustomerAIUnit::GetBlueprintClass() const
{
	int32 BPPathId = GetBlueprintPathId();
	if (BPPathId == INDEX_NONE)
	{
		return nullptr;
	}

	return UUtilityFunctions::GetClassByTablePathId(BPPathId);
}
