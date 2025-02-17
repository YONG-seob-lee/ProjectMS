// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectPersonalActionAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"


UMS_SelectPersonalActionAITask::UMS_SelectPersonalActionAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Select Personal Action";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SelectPersonalActionAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	EMS_PersonalActionType SelectedPersonalAction =  AIUnit->GetFirstPersonalAction();
	if (SelectedPersonalAction == EMS_PersonalActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::SelectedPersonalAction, static_cast<uint8>(SelectedPersonalAction));
	
	return EBTNodeResult::Type::Succeeded;
}