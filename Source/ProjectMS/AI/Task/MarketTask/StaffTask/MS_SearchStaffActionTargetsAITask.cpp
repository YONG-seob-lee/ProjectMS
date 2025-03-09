// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SearchStaffActionTargetsAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Units/MS_CounterUnit.h"
#include "Units/MS_StorageUnit.h"
#include "Units/MS_StaffAIUnit.h"


UMS_SearchStaffActionTargetsAITask::UMS_SearchStaffActionTargetsAITask(
	const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Search Staff Action Targets";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SearchStaffActionTargetsAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
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

	EMS_StaffActionType SelectedStaffAction = static_cast<EMS_StaffActionType>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffAction));
	if (SelectedStaffAction == EMS_StaffActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}

	// Issue
	if (SelectedStaffAction == EMS_StaffActionType::Issue)
	{
		EMS_StaffActionState ActionState = static_cast<EMS_StaffActionState>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffActionState));
		if (ActionState == EMS_StaffActionState::None)
		{
			return EBTNodeResult::Type::Failed;
		}

		// SearchRequestUnit
		if (ActionState == EMS_StaffActionState::Add_Delivery_SearchRequestUnit || ActionState == EMS_StaffActionState::Return_PickUp_SearchRequestUnit)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TWeakObjectPtr<UMS_UnitBase> RequestUnit = AIUnit->GetIssueTicketRequestUnit();

			if (RequestUnit != nullptr)
			{
				if (UMS_FurnitureUnit* RequestFurnitureUnit = Cast<UMS_FurnitureUnit>(RequestUnit))
				{
					const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
						RequestFurnitureUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseStorage);

					if (PropPurposeSpaceComponents.Num() != 0)
					{
						for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
						{
							TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
						}

						AIUnit->SetTargetPositions(TargetPositions);
						return EBTNodeResult::Type::Succeeded;
					}
				}
				else
				{
					MS_ERROR(TEXT("이 케이스에서는 스태프 유닛이 이슈를 넘겨받지 않으니 무조건 가구 유닛이어야 하는데..?"))
					MS_ENSURE(false);
				}
			}
			return EBTNodeResult::Type::Failed;
		}

		// SearchPickUpTargets
		if (ActionState == EMS_StaffActionState::Add_PickUp_SearchTargets)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TArray<TWeakObjectPtr<UMS_StorageUnit>> PickUpTargetUnits = {};
			if (AIUnit->GetIssueTicketPickUpTargetUnits(PickUpTargetUnits))
			{
				for (const TWeakObjectPtr<UMS_StorageUnit>& TargetUnit : PickUpTargetUnits)
				{
					const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
						TargetUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseStorage);

					if (PropPurposeSpaceComponents.Num() != 0)
					{
						for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
						{
							TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
						}
					}
				}
			}

			AIUnit->SetTargetPositions(TargetPositions);
			return TargetPositions.IsEmpty() ? EBTNodeResult::Type::Failed : EBTNodeResult::Type::Succeeded;
		}

		// SearchDeliveryTargets
		if (ActionState == EMS_StaffActionState::Return_Delivery_SearchTargets)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TArray<TWeakObjectPtr<UMS_StorageUnit>> DeliveryTargetUnits = {};
			if (AIUnit->GetIssueTicketDeliveryTargetUnits(DeliveryTargetUnits))
			{
				for (const TWeakObjectPtr<UMS_StorageUnit>& TargetUnit : DeliveryTargetUnits)
				{
					const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
						TargetUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseStorage);

					if (PropPurposeSpaceComponents.Num() != 0)
					{
						for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
						{
							TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
						}
					}
				}
			}

			AIUnit->SetTargetPositions(TargetPositions);
			return TargetPositions.IsEmpty() ? EBTNodeResult::Type::Failed : EBTNodeResult::Type::Succeeded;
		}

		if (ActionState == EMS_StaffActionState::Payment_SearchCounterUnit)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TArray<TWeakObjectPtr<UMS_UnitBase>> Units;
			gUnitMng.GetUnits(EMS_UnitType::Counter, Units);

			for (auto& Unit : Units)
			{
				if (UMS_CounterUnit* CounterUnit = Cast<UMS_CounterUnit>(Unit.Get()))
				{
					const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
							CounterUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::Cashier);
					
					for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
					{
						TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
					}
				}
			}

			AIUnit->SetTargetPositions(TargetPositions);
			return TargetPositions.IsEmpty() ? EBTNodeResult::Type::Failed : EBTNodeResult::Type::Succeeded;
		}
	}

	return EBTNodeResult::Type::Failed;
}
