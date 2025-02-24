#include "MS_ChangeStaffActionProcessAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Staff/MS_StaffAIAnimation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"


UMS_ChangeStaffActionProcessAITask::UMS_ChangeStaffActionProcessAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Change Staff Action Process";
	bNotifyTick = false;

	ActionProcess = EMS_StaffActionProcess::None;
}

EBTNodeResult::Type UMS_ChangeStaffActionProcessAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory)
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}
		
	const TObjectPtr<UMS_StaffAIAnimation> AIAnimInstance = Cast<UMS_StaffAIAnimation>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::CurrentActionProcess, static_cast<uint8>(ActionProcess));

	AIAnimInstance->SetActionProcess(ActionProcess);
	
	return EBTNodeResult::Type::Succeeded;
}
