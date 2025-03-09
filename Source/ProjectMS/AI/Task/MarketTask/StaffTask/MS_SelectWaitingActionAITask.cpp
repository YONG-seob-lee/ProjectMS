// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SelectWaitingActionAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Animation/Market/Staff/MS_StaffAIAnimInstance.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Units/MS_StaffAIUnit.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Units/MS_CounterUnit.h"


UMS_SelectWaitingActionAITask::UMS_SelectWaitingActionAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Select Waiting Action";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SelectWaitingActionAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	const TObjectPtr<UMS_StaffAIAnimInstance> AIAnimInstance = Cast<UMS_StaffAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	if (BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffAction) != static_cast<uint8>(EMS_StaffActionType::None))
	{
		return EBTNodeResult::Type::Failed;
	}

	if (BlackboardComp->GetValueAsEnum(StaffBoardKeyName::StaffIssueType) != static_cast<uint8>(EMS_StaffIssueType::None))
	{
		return EBTNodeResult::Type::Failed;
	}

	EMS_StaffActionState ActionState = EMS_StaffActionState::None;
	
	const FMS_PlayerStaffData StaffData  = AIUnit->GetPlayerStaffData();

	if (StaffData.PriorityOfWorks.IsValidIndex(0))
	{
		EMS_StaffIssueType Priority = StaffData.PriorityOfWorks[0];
		
		switch (Priority)
		{
		case EMS_StaffIssueType::Payment :
			{
				TArray<FIntVector2> TargetPositions = {};
			
				TArray<TWeakObjectPtr<UMS_UnitBase>> Units;
				gUnitMng.GetUnits(EMS_UnitType::Counter, Units);

				for (auto& Unit : Units)
				{
					if (UMS_CounterUnit* CounterUnit = Cast<UMS_CounterUnit>(Unit.Get()))
					{
						TWeakObjectPtr<UMS_StaffAIUnit> CounterStaff = CounterUnit->GetStaffUnit(true);
						if (CounterStaff == nullptr || CounterStaff == AIUnit)
						{
							ActionState = EMS_StaffActionState::None_SearchRandomCounterUnit;
							break;
						}
					}
				}

				if (ActionState == EMS_StaffActionState::None_SearchRandomCounterUnit) // Counter로 갈 수 없을 시 Display로 활동
				{
					break;
				}
			}
			
		case  EMS_StaffIssueType::ReturnItemsFromDisplay :
		case  EMS_StaffIssueType::AddItemsToDisplay :
			{
				float RandomValue = FMath::RandRange(0.f, 1.f);
				if (RandomValue <= MovePercentage)
				{
					ActionState = EMS_StaffActionState::None_SearchRandomPoint_Display;
				}
				else
				{
					ActionState = EMS_StaffActionState::None_Idle;
				}
				
				break;
			}
			
		case  EMS_StaffIssueType::ReturnItemsFromShelf :
		case  EMS_StaffIssueType::AddItemsToShelf :
			{
				float RandomValue = FMath::RandRange(0.f, 1.f);
				if (RandomValue <= MovePercentage)
				{
					ActionState = EMS_StaffActionState::None_SearchRandomPoint_Shelf;
				}
				else
				{
					ActionState = EMS_StaffActionState::None_Idle;
				}
				
				break;
			}

		default:
			{
				break;
			}	
		}
	}

	if (ActionState == EMS_StaffActionState::None)
	{
		ActionState = EMS_StaffActionState::None_Idle;
	}
	
	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffActionState, static_cast<uint8>(ActionState));

	AIAnimInstance->SetActionState(ActionState);
	
	return EBTNodeResult::Type::Succeeded;
}
