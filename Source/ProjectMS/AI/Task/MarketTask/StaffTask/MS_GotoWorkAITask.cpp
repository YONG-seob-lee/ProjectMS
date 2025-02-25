// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GotoWorkAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Animation/Market/Staff/MS_StaffAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"

UMS_GotoWorkAITask::UMS_GotoWorkAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Go to Work";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_GotoWorkAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_StaffAIController> AIController = Cast<AMS_StaffAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_StaffAICharacter> AICharacter = Cast<AMS_StaffAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_StaffAIUnit> AIUnit = Cast<UMS_StaffAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_StaffAIAnimInstance> StaffAIAnimInstance = Cast<UMS_StaffAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!StaffAIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	if(AIUnit->FindNearestSpline() == false)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	StaffAIAnimInstance->SetActionProcess(EMS_StaffActionState::MoveUsingSpline);
	
	return EBTNodeResult::Type::InProgress;
}

void UMS_GotoWorkAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	const TObjectPtr<AMS_StaffAIController> AIController = Cast<AMS_StaffAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return;
	}

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
	
	if(AIUnit->ReachSplineEndPoint())
	{
		BlackboardComp->SetValueAsEnum(StaffBoardKeyName::CurrentActionProcess, static_cast<uint8>(EMS_StaffActionState::None));
		StaffAIAnimInstance->SetActionProcess(EMS_StaffActionState::None);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		AIUnit->GoingToWork();
	}
}
