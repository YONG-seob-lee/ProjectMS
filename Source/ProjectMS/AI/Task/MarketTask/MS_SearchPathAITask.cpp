// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SearchPathAITask.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Units/MS_StaffAIUnit.h"

UMS_SearchPathAITask::UMS_SearchPathAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Search Path";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_SearchPathAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	TObjectPtr<UMS_ModeStateBase> ModeState = gModeMng.GetCurrentModeState();
	if (ModeState == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	TArray<FIntVector2> Path = {};
	bool bSearchGate = false;
	
	ModeState->SearchPathToTargetOrGate(Path, bSearchGate, AIUnit->GetGridPosition(), AIUnit->GetTargetPositions());

	AIUnit->SetPath(Path);
	return EBTNodeResult::Type::Succeeded;
}

void UMS_SearchPathAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}
