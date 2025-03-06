// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SetSplineEndPointAsSearchTargetsAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"

UMS_SetSplineEndPointAsSearchTargetsAITask::UMS_SetSplineEndPointAsSearchTargetsAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set SplineEndPoint As Search Targets";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SetSplineEndPointAsSearchTargetsAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	TArray<FIntVector2> TargetPosition;
	TargetPosition.Emplace(FMS_GridData::ConvertLocationToGridPosition(AIUnit->GetSplineEndPointPosition()));
	AIUnit->SetTargetPositions(TargetPosition);

	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}
	const EMS_CustomerActionState CurrentActionState = static_cast<EMS_CustomerActionState>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerActionState));

	if(CurrentActionState == EMS_CustomerActionState::GoToSplineEndPointWithAngry)
	{
		AIUnit->ResetChatting();
		AIUnit->EventChattingImage(EMS_SpeechImageType::Angry);
		AIUnit->EventBehavior(EMS_BehaviorType::VeryAngry);
	}
	return EBTNodeResult::Type::Succeeded;
}
