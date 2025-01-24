// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AIParameterComponent.h"

#include "MS_UnitBase.h"


UMS_AIParameterComponent::UMS_AIParameterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_AIParameterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMS_AIParameterComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const TObjectPtr<UMS_UnitBase> ParentUnit = Cast<UMS_UnitBase>(GetOuter()))
	{
		UnitHandle = ParentUnit->GetUnitHandle();
	}
}

void UMS_AIParameterComponent::BehaviorTrigger(EMS_BehaviorType aBehaviorType)
{
	switch(aBehaviorType)
	{
	case EMS_BehaviorType::ComeInMarket:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::ComeInMarket);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::ComeOutMarket:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::ComeOutMarket);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::FindItem:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::FindItem);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::TalkToStaff:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::TalkToStaff);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::LostWay:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::LostWay);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::PickUpItem:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::PickUpItem);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::BuyItem:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::BuyItem);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), Behavior));
			break;
		}
	default:
		{
			break;
		}
	}
}

void UMS_AIParameterComponent::PurchaseTrigger(int32 aItemId, int32 aItemCount) const
{
	gUnitMng.OnPurchaseDelegate.Broadcast(FMS_PurchaseParameter(UnitHandle, aItemId, aItemCount));
}
