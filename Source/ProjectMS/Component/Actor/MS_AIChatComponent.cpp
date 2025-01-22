// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AIChatComponent.h"

#include "MS_UnitBase.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ScheduleManager.h"


UMS_AIChatComponent::UMS_AIChatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMS_AIChatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMS_AIChatComponent::BeginPlay()
{
	Super::BeginPlay();

	if(const TObjectPtr<UMS_UnitBase> ParentUnit = Cast<UMS_UnitBase>(GetOuter()))
	{
		UnitHandle = ParentUnit->GetUnitHandle();
	}

	// 나중에 AI 이벤트가 활성화 되는 트리거를 통해 추가적으로 브로드캐스트
	const FString LocalizedTableString = TEXT("Customer_Comment_01");
	gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitHandle, gScheduleMng.GetCurrentMinute(), LocalizedTableString));
}