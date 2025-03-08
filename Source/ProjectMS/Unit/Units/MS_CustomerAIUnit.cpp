// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerAIUnit.h"

#include "MS_ActorUnitBase.h"
#include "UtilityFunctions.h"
#include "Character/MS_CharacterBase.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Prop/Spline/MS_CustomerSplineActor.h"
#include "Table/Caches/MS_CustomerCacheTable.h"

void UMS_CustomerAIUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	const TObjectPtr<UMS_CustomerCacheTable> CustomerTable = Cast<UMS_CustomerCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Customer));
	MS_ENSURE(CustomerTable);

	CustomerTable->MakeNewCustomerData(CustomerData);

	// ToDo : SlotCount 설정 (테이블 기반, 장비에 따라 추가)
	int32 SlotCount = 2;
	for (int32 i = 0; i < SlotCount; ++i)
	{
		SlotDatas.Emplace(FMS_SlotData());
	}
}

void UMS_CustomerAIUnit::Finalize()
{
	Super::Finalize();
}

void UMS_CustomerAIUnit::PostInitialize()
{
	Super::PostInitialize();
	
	if(const TObjectPtr<AMS_CustomerAICharacter> CustomerAICharacter = Cast<AMS_CustomerAICharacter>(GetCharacter()))
	{
		CustomerAICharacter->PostInitialize(UnitHandle);
	}
}

void UMS_CustomerAIUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

int32 UMS_CustomerAIUnit::GetBlueprintPathId() const
{
	return CustomerData.GetCharacterBPPathFile();
}

UClass* UMS_CustomerAIUnit::GetBlueprintClass() const
{
	const int32 BPPathId = GetBlueprintPathId();
	if (BPPathId == INDEX_NONE)
	{
		return nullptr;
	}

	return UUtilityFunctions::GetClassByTablePathId(BPPathId);
}

EMS_CustomerActionType UMS_CustomerAIUnit::GetFirstCustomerAction()
{
	if (CustomerActions.IsValidIndex(0))
	{
		MS_ENSURE (CustomerActions[0] != EMS_CustomerActionType::None);
	}
	else
	{
		if(CustomerData.IsAnyPickUpItemsNotHave())
		{
			if(IsAnyItemInDisplay())
			{
				CustomerActions.Emplace(EMS_CustomerActionType::PickUpItems);
			}
			else
			{
				CustomerActions.Emplace(EMS_CustomerActionType::AngryAndGoHome);
			}
		}
		else
		{
			// 원하는 아이템 종류중 하나라도 비어있으면
			if(CustomerData.IsExceptAnyWannaItem())
			{
				CustomerActions.Emplace(EMS_CustomerActionType::AngryAndGoHome);
			}
			else
			{
				if(CustomerData.GetPaid() == false)
				{
					CustomerActions.Emplace(EMS_CustomerActionType::Payment);
				}
				else
				{
					CustomerActions.Emplace(EMS_CustomerActionType::GoHome);
				}	
			}
		}	
	}
	
	return CustomerActions[0];
}

void UMS_CustomerAIUnit::RegisterCustomerAction(EMS_CustomerActionType aCustomerActionType)
{
	CustomerActions.Emplace(aCustomerActionType);
}

void UMS_CustomerAIUnit::UnregisterCustomerAction(EMS_CustomerActionType aCustomerActionType)
{
	CustomerActions.RemoveSingle(aCustomerActionType);
}

bool UMS_CustomerAIUnit::IsVisitBefore(int32 StorageUnitHandle) const
{
	if(VisitStorageUnitHandles.Find(StorageUnitHandle) == INDEX_NONE)
	{
		return false;
	}
	
	return true;
}

void UMS_CustomerAIUnit::AddVisitStorageUnitHandle(MS_Handle StorageHandle)
{
	VisitStorageUnitHandles.Emplace(StorageHandle);
}

MS_Handle UMS_CustomerAIUnit::GetTargetStorageUnitHandle()
{
	if(VisitStorageUnitHandles.Num() > 0)
	{
		return VisitStorageUnitHandles.Last();
	}
	
	return INDEX_NONE;
}

bool UMS_CustomerAIUnit::IsAnyItemInDisplay()
{
	TMap<int32, int32> DisplayItems;
	gItemMng.GetStorageItems(EMS_ZoneType::Display, DisplayItems);

	if(DisplayItems.Num() == 0)
	{
		return false;
	}

	return true;
}

void UMS_CustomerAIUnit::GetRemainItems(TMap<int32, int32>& RemainItems)
{
	CustomerData.GetRemainItems(RemainItems);
}

void UMS_CustomerAIUnit::PickUpItem(int32 PickUpItemTableId, int32 PickUpItemCount)
{
	CustomerData.PickUpItem(PickUpItemTableId, PickUpItemCount);
	if(const TObjectPtr<AMS_CustomerAICharacter> CustomerAICharacter = Cast<AMS_CustomerAICharacter>(GetCharacter()))
	{
		CustomerAICharacter->PickUp(PickUpItemTableId);
	}
}

void UMS_CustomerAIUnit::ShowPickItem(bool bShow) const
{
	if(const TObjectPtr<AMS_CustomerAICharacter> CustomerAICharacter = Cast<AMS_CustomerAICharacter>(GetCharacter()))
	{
		CustomerAICharacter->ShowPickUp(bShow);
	}
}

void UMS_CustomerAIUnit::Paid()
{
	CustomerData.Paid();
}

bool UMS_CustomerAIUnit::IsPickUpAllItems()
{
	return CustomerData.IsPickUpAllItems();
}

bool UMS_CustomerAIUnit::IsExceptAnyWannaItem()
{
	return CustomerData.IsExceptAnyWannaItem();
}

bool UMS_CustomerAIUnit::FindNearestSpline()
{
	TArray<TWeakObjectPtr<UMS_UnitBase>> DuckSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::CustomerSpline, DuckSplineUnits);

	float DistanceMin = 0.f;
	TWeakObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
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

	if(NearestSplineUnit == nullptr)
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

FVector UMS_CustomerAIUnit::GetSplineEndPointPosition() const
{
	if(CustomerSplineActor.IsValid() == false)
	{
		return FVector::ZeroVector;
	}

	return CustomerSplineActor->GetEndPoint();
}

bool UMS_CustomerAIUnit::ReachSplineStartPoint() const
{
	if(CustomerSplineActor.IsValid() == false)
	{
		return false;
	}
	const FVector ActorLocation = GetActorLocation();
	const FVector SplineEndPoint = CustomerSplineActor->GetStartPoint();
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

void UMS_CustomerAIUnit::GoingToHome() const
{
	if(CustomerSplineActor.IsValid())
	{
		const FVector CurrentVehicleLocation = GetActorLocation();
		const FVector TangentLocation = -CustomerSplineActor->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
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

void UMS_CustomerAIUnit::EventBehavior(EMS_BehaviorType aBehaviorType) const
{
	if(const TObjectPtr<AMS_CustomerAICharacter> CustomerAICharacter = Cast<AMS_CustomerAICharacter>(GetCharacter()))
	{
		CustomerAICharacter->EventBehavior(aBehaviorType);
	}
}

void UMS_CustomerAIUnit::EventPurchase(TMap<int32, int32>& PickUpItems) const
{
	if(const TObjectPtr<AMS_CustomerAICharacter> CustomerAICharacter = Cast<AMS_CustomerAICharacter>(GetCharacter()))
	{
		CustomerData.GetAllPickUpItem(PickUpItems);
		CustomerAICharacter->EventPurchase(PickUpItems);
	}
}
