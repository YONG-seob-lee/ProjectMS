// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitBehaviorCollectComponent.h"

#include "Manager_Both/MS_UnitManager.h"

void UMS_UnitBehaviorCollectComponent::Initialize()
{
	Super::Initialize();
	gUnitMng.OnBehaviorDelegate.AddUObject(this, &UMS_UnitBehaviorCollectComponent::SetOnUpdateBehavior);
}

void UMS_UnitBehaviorCollectComponent::Finalize()
{
	gUnitMng.OnBehaviorDelegate.RemoveAll(this);
}

void UMS_UnitBehaviorCollectComponent::SetOnUpdateBehavior(FMS_BehaviorParameter aParameter)
{
	if(TArray<FMS_BehaviorParameter>* Parameters = BehaviorCollection.Find(aParameter.UnitHandle))
	{
		Parameters->Emplace(aParameter);
		TimelineBehaviorCollection.Emplace(aParameter);
	}
	else
	{
		MS_LOG(TEXT("Wrong Process!"));
	}
}

void UMS_UnitBehaviorCollectComponent::GetUnitBehavior(MS_Handle aUnitHandle, TArray<FMS_BehaviorParameter>& aParameters)
{
	aParameters.Empty();

	if(const TArray<FMS_BehaviorParameter>* Parameters = BehaviorCollection.Find(aUnitHandle))
	{
		aParameters = *Parameters;
	}
}

void UMS_UnitBehaviorCollectComponent::GetAllBehavior(TArray<FMS_BehaviorParameter>& aBehaviorCollection) const
{
	aBehaviorCollection.Empty();

	aBehaviorCollection = TimelineBehaviorCollection;
}
