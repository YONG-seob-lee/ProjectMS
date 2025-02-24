// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SearchStaffActionTargetsAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_FurnitureUnit.h"
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

	EMS_StaffActionType SelectedStaffAction = static_cast<EMS_StaffActionType>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::SelectedStaffAction));
	if (SelectedStaffAction == EMS_StaffActionType::None)
	{
		return EBTNodeResult::Type::Failed;
	}

	// Issue
	if (SelectedStaffAction == EMS_StaffActionType::Issue)
	{
		EMS_StaffActionProcess ActionProcess = static_cast<EMS_StaffActionProcess>(BlackboardComp->GetValueAsEnum(StaffBoardKeyName::CurrentActionProcess));
		if (ActionProcess == EMS_StaffActionProcess::None)
		{
			return EBTNodeResult::Type::Failed;
		}

		// SearchRequestUnit
		if (ActionProcess == EMS_StaffActionProcess::SearchRequestUnitForAdd2_TakeIn || ActionProcess == EMS_StaffActionProcess::SearchRequestUnitForReturn1_TakeOut)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TWeakObjectPtr<UMS_FurnitureUnit> RequestUnit = AIUnit->GetIssueTicketRequestFurnitrueUnit();

			const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
				RequestUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseStorage);

			if (PropPurposeSpaceComponents.Num() != 0)
			{
				for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
				{
					TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
				}

				AIUnit->SetTargetPositions(TargetPositions);
				return EBTNodeResult::Type::Succeeded;
			}
			return EBTNodeResult::Type::Failed;
		}

		// SearchTakeOutTargets
		if (ActionProcess == EMS_StaffActionProcess::SearchTargetsForAdd1_TakeOut)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TArray<TWeakObjectPtr<UMS_FurnitureUnit>> TakeOutTargetUnits = {};
			if (AIUnit->GetIssueTicketTakeOutTargetUnits(TakeOutTargetUnits))
			{
				for (const TWeakObjectPtr<UMS_FurnitureUnit>& TargetUnit : TakeOutTargetUnits)
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

		// SearchTakeOutTargets
		if (ActionProcess == EMS_StaffActionProcess::SearchTargetsForReturn2_TakeIn)
		{
			TArray<FIntVector2> TargetPositions = {};
			
			TArray<TWeakObjectPtr<UMS_FurnitureUnit>> TakeInTargetUnits = {};
			if (AIUnit->GetIssueTicketTakeInTargetUnits(TakeInTargetUnits))
			{
				for (const TWeakObjectPtr<UMS_FurnitureUnit>& TargetUnit : TakeInTargetUnits)
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
	}

	// Change Clothes
	else if (SelectedStaffAction == EMS_StaffActionType::ChangeClothes)
	{
		TArray<FIntVector2> TargetPositions = {};
		
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		gUnitMng.GetUnits(EMS_UnitType::Furniture,Units);

		for (const TObjectPtr<UMS_UnitBase>& Unit : Units)
		{
			UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit);
			if (!IsValid(FurnitureUnit))
			{
				MS_ENSURE(false);
				continue;
			}
			
			const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
				FurnitureUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseWardrobe);

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

	return EBTNodeResult::Type::Failed;
}
