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

	if (SelectedStaffAction == EMS_StaffActionType::ChangeClothes)
	{
		TArray<TObjectPtr<UMS_UnitBase>> Units;
		gUnitMng.GetUnits(EMS_UnitType::Furniture,Units);

		for (const TObjectPtr<UMS_UnitBase>& Unit : Units)
		{
			UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(Unit);
			if (!IsValid(FurnitureUnit))
			{
				MS_ENSURE(false);
				return EBTNodeResult::Type::Failed;
			}
			
			const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents =
				FurnitureUnit->GetPropPurposeSpaceComponents(EMS_PurposeType::UseWardrobe);

			if (PropPurposeSpaceComponents.Num() == 0)
			{
				MS_ERROR(TEXT("[%s] Prop purpose space for use wardrobe don't exist"), *MS_FUNC_STRING);
				return EBTNodeResult::Type::Failed;
			}

			TArray<FIntVector2> TargetPositions;
			for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
			{
				TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
			}

			AIUnit->SetTargetPositions(TargetPositions);
			return EBTNodeResult::Type::Succeeded;
		}
	}

	return EBTNodeResult::Type::Failed;
}
