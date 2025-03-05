// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GotoMarketAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"


UMS_GotoMarketAITask::UMS_GotoMarketAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Go to Market";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_GotoMarketAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_CustomerAIAnimInstance> CustomerAIAnimInstance = Cast<UMS_CustomerAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!CustomerAIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	if(AIUnit->FindNearestSpline() == false)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	return EBTNodeResult::Type::InProgress;
}

void UMS_GotoMarketAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}

	const TObjectPtr<UMS_CustomerAIAnimInstance> CustomerAIAnimInstance = Cast<UMS_CustomerAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!CustomerAIAnimInstance)
	{
		return;
	}
	
	if(AIUnit->ReachSplineEndPoint())
	{
		AIUnit->EventBehavior(EMS_BehaviorType::ComeInMarket);
		BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffActionState, static_cast<uint8>(EMS_CustomerActionState::None));
		CustomerAIAnimInstance->SetActionState(EMS_CustomerActionState::None);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		AIUnit->GoingToMarket();
	}
}
