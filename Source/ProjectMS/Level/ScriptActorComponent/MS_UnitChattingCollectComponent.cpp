// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitChattingCollectComponent.h"

#include "Manager_Both/MS_UnitManager.h"

void UMS_UnitChattingCollectComponent::Initialize()
{
	gUnitMng.OnChattingDelegate.AddUObject(this, &UMS_UnitChattingCollectComponent::SetOnUpdateChatting);
}

void UMS_UnitChattingCollectComponent::Finalize() const
{
	gUnitMng.OnChattingDelegate.RemoveAll(this);
}

void UMS_UnitChattingCollectComponent::SetOnUpdateChatting(FMS_ChattingParameter aParameter)
{
	if(TArray<FMS_ChattingParameter>* Parameters = ChattingCollection.Find(aParameter.UnitHandle))
	{
		Parameters->Emplace(aParameter);
		TimelineChattingCollection.Emplace(aParameter);
	}
	else
	{
		MS_LOG(TEXT("Cheat Process!"));
		TArray<FMS_ChattingParameter> UnitChattingParameterArray;
		UnitChattingParameterArray.Emplace(aParameter);
		ChattingCollection.Emplace(aParameter.UnitHandle, UnitChattingParameterArray);
		TimelineChattingCollection.Emplace(aParameter);
	}
}

void UMS_UnitChattingCollectComponent::GetUnitsHandle(TMap<MS_Handle, bool>& aUnitsHandle)
{
	aUnitsHandle.Empty();
	
	for(const auto& Chatting : ChattingCollection)
	{
		aUnitsHandle.Emplace(Chatting.Key, Chatting.Value.Last().bIsInMarket);
	}
}

void UMS_UnitChattingCollectComponent::GetUnitChatting(MS_Handle aUnitHandle, TArray<FMS_ChattingParameter>& aParameters)
{
	aParameters.Empty();

	if(const TArray<FMS_ChattingParameter>* Parameters = ChattingCollection.Find(aUnitHandle))
	{
		aParameters = *Parameters;
	}
}

void UMS_UnitChattingCollectComponent::GetAllChatting(TArray<FMS_ChattingParameter>& aChattingCollection) const
{
	aChattingCollection.Empty();

	aChattingCollection = TimelineChattingCollection;
}
