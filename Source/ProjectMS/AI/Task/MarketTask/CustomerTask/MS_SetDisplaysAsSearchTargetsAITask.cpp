// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SetDisplaysAsSearchTargetsAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StorageUnit.h"

UMS_SetDisplaysAsSearchTargetsAITask::UMS_SetDisplaysAsSearchTargetsAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set Displays As Search Targets";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SetDisplaysAsSearchTargetsAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	if (static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction)) != EMS_CustomerActionType::PickUpItems)
	{
		return EBTNodeResult::Type::Failed;
	}

	TArray<TObjectPtr<UMS_UnitBase>> Units;
	gUnitMng.GetUnits(EMS_UnitType::Storage, Units);

	TArray<FIntVector2> TargetPositions = {};
	
	for (const TObjectPtr<UMS_UnitBase>& Unit : Units)
	{
		const UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit);
		if (!IsValid(StorageUnit))
		{
			MS_ENSURE(false);
			continue;
		}

		if(StorageUnit->GetZoneType() != EMS_ZoneType::Display)
		{
			continue;
		}
		
		if(AIUnit->IsVisitBefore(StorageUnit->GetUnitHandle()) == false)
		{
			const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents = StorageUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseStorage);

			if (PropPurposeSpaceComponents.Num() == 0)
			{
				continue;
			}
			
			for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
			{
				TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
			}

			AIUnit->AddVisitStorageUnitHandle(StorageUnit->GetUnitHandle());
			break;
		}
	}
	
	AIUnit->SetTargetPositions(TargetPositions);
	return TargetPositions.IsEmpty() ? EBTNodeResult::Type::Failed : EBTNodeResult::Type::Succeeded;
}
