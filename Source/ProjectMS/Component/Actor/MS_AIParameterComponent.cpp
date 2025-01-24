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

void UMS_AIParameterComponent::PurchaseTrigger(int32 aItemId, int32 aItemCount) const
{
	gUnitMng.OnPurchaseDelegate.Broadcast(FMS_PurchaseParameter(UnitHandle, aItemId, aItemCount));
}
