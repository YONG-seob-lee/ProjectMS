// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GotoHomeAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "Animation/Market/Staff/MS_StaffAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StaffAIUnit.h"

UMS_GotoHomeAITask::UMS_GotoHomeAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Go to Home";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_GotoHomeAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type::InProgress;
}

void UMS_GotoHomeAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if(const TObjectPtr<AMS_CustomerAIController> CustomerAIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner()))
	{
		CustomerTickTask(OwnerComp, CustomerAIController);
	}

	if(const TObjectPtr<AMS_StaffAIController> StaffAIController = Cast<AMS_StaffAIController>(OwnerComp.GetAIOwner()))
	{
		StaffTickTask(OwnerComp, StaffAIController);
	}
}

void UMS_GotoHomeAITask::StaffTickTask(UBehaviorTreeComponent& OwnerComp, const TObjectPtr<AMS_StaffAIController> AIController) const
{
	const TObjectPtr<AMS_StaffAICharacter> AICharacter = Cast<AMS_StaffAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return;
	}

	const TObjectPtr<UMS_StaffAIAnimInstance> StaffAIAnimInstance = Cast<UMS_StaffAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!StaffAIAnimInstance)
	{
		return;
	}
	
	if(AIUnit->ReachSplineStartPoint())
	{
		BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffActionState, static_cast<uint8>(EMS_StaffActionState::None));
		StaffAIAnimInstance->SetActionState(EMS_StaffActionState::None);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		AIUnit->GoingToHome();
	}
}

void UMS_GotoHomeAITask::CustomerTickTask(UBehaviorTreeComponent& OwnerComp, const TObjectPtr<AMS_CustomerAIController> AIController) const
{
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
	
	// const EMS_CustomerActionType CustomerActionType = static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction));
	// const EMS_CustomerActionState State = static_cast<EMS_CustomerActionState>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerActionState));
	if(AIUnit->ReachSplineStartPoint())
	{
		CustomerAIAnimInstance->SetActionState(EMS_CustomerActionState::None);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		AIUnit->GoingToHome();
	}
}
