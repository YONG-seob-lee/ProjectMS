// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PositionAfterPaymentAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Units/MS_CounterUnit.h"
#include "Units/MS_CustomerAIUnit.h"

UMS_PositionAfterPaymentAITask::UMS_PositionAfterPaymentAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Position Before Payment";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_PositionAfterPaymentAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	const EMS_CustomerActionType SelectedCustomerAction = static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction));
	if (SelectedCustomerAction != EMS_CustomerActionType::Payment)
	{
		return EBTNodeResult::Type::Failed;
	}

	TArray<TWeakObjectPtr<UMS_UnitBase>> Units;
	gUnitMng.GetUnits(EMS_UnitType::Counter, Units);

	TArray<FIntVector2> TargetPositions = {};
	
	for (const TWeakObjectPtr<UMS_UnitBase>& Unit : Units)
	{
		UMS_CounterUnit* CounterUnit = Cast<UMS_CounterUnit>(Unit);
		if (!IsValid(CounterUnit))
		{
			MS_ENSURE(false);
			continue;
		}
		
		const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
				CounterUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::AfterPayment);

		if (PropPurposeSpaceComponents.Num() == 0)
		{
			continue;
		}
			
		for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
		{
			TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
		}
	}

	AIUnit->SetTargetPositions(TargetPositions);
	return TargetPositions.IsEmpty() ? EBTNodeResult::Type::Failed : EBTNodeResult::Type::Succeeded;
}
