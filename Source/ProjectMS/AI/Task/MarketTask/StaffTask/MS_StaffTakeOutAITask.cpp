#include "MS_StaffTakeOutAITask.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Staff/MS_StaffAIAnimation.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"

UMS_StaffTakeOutAITask::UMS_StaffTakeOutAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Staff Take Out";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_StaffTakeOutAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	// AIAnimInstance->SetActionProcess(EMS);
	return EBTNodeResult::Type::InProgress;
}
