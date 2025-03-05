// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AIParameterComponent.h"

#include "MS_UnitBase.h"
#include "Units/MS_CustomerAIUnit.h"


UMS_AIParameterComponent::UMS_AIParameterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_AIParameterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMS_AIParameterComponent::Initialize(MS_Handle aUnitHandle)
{
	UnitHandle = aUnitHandle;
}

void UMS_AIParameterComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_AIParameterComponent::BehaviorTrigger(EMS_BehaviorType aBehaviorType)
{
	switch(aBehaviorType)
	{
	case EMS_BehaviorType::ComeInMarket:
		{
			const TObjectPtr<UMS_CustomerAIUnit> CustomerUnit = Cast<UMS_CustomerAIUnit>(gUnitMng.GetUnit(UnitHandle));
			if(!CustomerUnit)
			{
				break;
			}
			const FText Behavior = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::ComeInMarket), FText::FromString(CustomerUnit->GetCustomerName()));
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::ComeOutMarket:
		{
			const TObjectPtr<UMS_CustomerAIUnit> CustomerUnit = Cast<UMS_CustomerAIUnit>(gUnitMng.GetUnit(UnitHandle));
			if(!CustomerUnit)
			{
				break;
			}
			const FText Behavior = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::ComeOutMarket), FText::FromString(CustomerUnit->GetCustomerName()));
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::FindItem:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::FindItem);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::TalkToStaff:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::TalkToStaff);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::LostWay:
		{
			const TObjectPtr<UMS_CustomerAIUnit> CustomerUnit = Cast<UMS_CustomerAIUnit>(gUnitMng.GetUnit(UnitHandle));
			if(!CustomerUnit)
			{
				break;
			}
			const FText Behavior = FText::Format(FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::LostWay), FText::FromString(CustomerUnit->GetCustomerName()));
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::PickUpItem:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::PickUpItem);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
			break;
		}
	case EMS_BehaviorType::BuyItem:
		{
			const FText Behavior = FText::FromStringTable(MS_LocalizedTableId::StringTable, BehaviorLocalizedString::BuyItem);
			gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitHandle, gScheduleMng.GetMinute(), Behavior));
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
