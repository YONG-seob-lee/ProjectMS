// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PutDownItemCustomerAITack.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Widget/Dialog/SpeechBubble/MS_SpeechBubbleWidget.h"

UMS_PutDownItemCustomerAITack::UMS_PutDownItemCustomerAITack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Put Down Items";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_PutDownItemCustomerAITack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	AIUnit->ShowPickItem(false);
	// AITest 나중에 Staff가 결제 하는 시간을 추가로 PaidTime 에다 기입해야한다.
	AIUnit->ResetChatting();
	PutDownProcessTime = 0.f;
	PutDownTime = 3.f;
	return EBTNodeResult::Type::InProgress;
}

void UMS_PutDownItemCustomerAITack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if(PutDownProcessTime > PutDownTime)
	{
		const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
		if(!BlackboardComp)
		{
			return;
		}

		BlackboardComp->SetValueAsBool(CustomerBoardKeyName::IsCustomerPutDownAllItems, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	PutDownProcessTime += DeltaSeconds;

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
	
	if(AIUnit->IsChatBefore() == false)
	{
		AIUnit->EventChattingImage(EMS_SpeechImageType::PutDownItems);
	}
}
