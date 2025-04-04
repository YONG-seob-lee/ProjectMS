﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PaymentInProgressAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Units/MS_CounterUnit.h"
#include "Units/MS_CustomerAIUnit.h"


UMS_PaymentInProgressAITask::UMS_PaymentInProgressAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Payment In Progress";
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMS_PaymentInProgressAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_CustomerAIController> AIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_CustomerAICharacter> AICharacter = Cast<AMS_CustomerAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}

	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = AIUnit->GetInteractableFurnitureUnit();
	CounterUnit = Cast<UMS_CounterUnit>(FurnitureUnit);
	if (CounterUnit != nullptr)
	{
		// AITest 나중에 Staff가 결제 하는 시간을 추가로 PaidTime 에다 기입해야한다.
		AIUnit->ResetChatting();
		PaidProcessTime = 0.f;
		PaidTime = 3.f;
		return EBTNodeResult::Type::InProgress;
	}
	
	return EBTNodeResult::Type::Failed;
}

void UMS_PaymentInProgressAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_CustomerAIController> AIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return;
	}

	const TObjectPtr<AMS_CustomerAICharacter> AICharacter = Cast<AMS_CustomerAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return;
	}

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return;
	}

	if (CounterUnit == nullptr)
	{
		return;
	}

	if (CounterUnit->GetStaffUnit(false) == nullptr)
	{
		return;
	}

	TWeakObjectPtr<UMS_CustomerAIUnit> CounterCustomerUnit = CounterUnit->GetFirstCustomerUnit();
	if (CounterCustomerUnit == nullptr || CounterCustomerUnit != AIUnit)
	{
		return;
	}
	
	if(PaidProcessTime > PaidTime)
	{
		// 데이터 수집
		AIUnit->EventBehavior(EMS_BehaviorType::BuyItem);
		TMap<int32, int32> PickUpItems;
		AIUnit->EventPurchase(PickUpItems);

		// 아이템 및 돈 정산
		gItemMng.PurchaseItems(PickUpItems);
		gItemMng.EarnMoney(PickUpItems);
		gItemMng.OnUpdateEarnMoneyDelegate.Broadcast(true);

		// 유닛 데이터 정리
		AIUnit->ShowPickItem(true);
		AIUnit->Paid();
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	PaidProcessTime += DeltaSeconds;

	if(AIUnit->IsChatBefore() == false)
	{
		AIUnit->EventChattingImage(EMS_SpeechImageType::Pay);
	}
}

void UMS_PaymentInProgressAITask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	const TObjectPtr<AMS_CustomerAIController> AIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return;
	}

	const TObjectPtr<AMS_CustomerAICharacter> AICharacter = Cast<AMS_CustomerAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return;
	}

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return;
	}
	
	if (CounterUnit != nullptr)
	{
		CounterUnit->UnregisterCustomerUnit(AIUnit);
	}
	
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
