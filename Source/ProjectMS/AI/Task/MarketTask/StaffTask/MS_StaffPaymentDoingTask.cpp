// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffPaymentDoingTask.h"

#include "AI/AIController/MS_AIController.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Units/MS_CounterUnit.h"
#include "Units/MS_StaffAIUnit.h"


UMS_StaffPaymentDoingTask::UMS_StaffPaymentDoingTask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Payment Doing";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_StaffPaymentDoingTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}

	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = AIUnit->GetInteractableFurnitureUnit();
	CounterUnit = Cast<UMS_CounterUnit>(FurnitureUnit);
	if (CounterUnit != nullptr)
	{
		return EBTNodeResult::Type::InProgress;
	}
	
	return EBTNodeResult::Type::Failed;
}

void UMS_StaffPaymentDoingTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	if (CounterUnit == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Failed);
		return;
	}

	TWeakObjectPtr<UMS_IssueTicket> IssueTicket;
	EMS_StaffActionType ActionType = AIUnit->GetFirstStaffAction(IssueTicket);
	
	if (ActionType == EMS_StaffActionType::Issue && IssueTicket != nullptr)
	{
		if (IssueTicket->GetRequestUnit() == CounterUnit)
		{
			return;	// 계속 진행
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);	// 일단 State를 PaymentWaiting으로 바꾼 다음 대기 or 다음 이슈 탐색으로 넘어가게 함
}
