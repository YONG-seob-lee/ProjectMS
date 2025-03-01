#include "MS_ChangeStaffActionStateAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/Staff/MS_StaffAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"


UMS_ChangeStaffActionStateAITask::UMS_ChangeStaffActionStateAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Change Staff Action State";
	bNotifyTick = false;

	ActionState = EMS_StaffActionState::None;
}

EBTNodeResult::Type UMS_ChangeStaffActionStateAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
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

	BlackboardComp->SetValueAsEnum(StaffBoardKeyName::StaffActionState, static_cast<uint8>(ActionState));

	AIAnimInstance->SetActionState(ActionState);
	
	return EBTNodeResult::Type::Succeeded;
}
