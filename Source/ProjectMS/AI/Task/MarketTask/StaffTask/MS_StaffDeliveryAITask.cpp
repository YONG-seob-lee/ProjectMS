﻿#include "MS_StaffDeliveryAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/MS_MarketAIAnimInstance.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_StaffAIUnit.h"


UMS_StaffDeliveryAITask::UMS_StaffDeliveryAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Delivery";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_StaffDeliveryAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (!AIUnit->DeliveryItems())
	{
		return EBTNodeResult::Type::Failed;
	}
	
	return EBTNodeResult::Type::InProgress;
}

void UMS_StaffDeliveryAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return;
	}
		
	const TObjectPtr<UMS_MarketAIAnimInstance> AIAnimInstance = Cast<UMS_MarketAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return;
	}

	if (!AIAnimInstance->IsInAction())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}
