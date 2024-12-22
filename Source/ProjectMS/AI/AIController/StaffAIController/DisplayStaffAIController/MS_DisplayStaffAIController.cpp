#include "AI/AIController/StaffAIController/DisplayStaffAIController/MS_DisplayStaffAIController.h"

#include "AI/AIController/StaffAIController/DisplayStaffAIController/BehaviorTree/Blackboard/MS_DisplayStaffBlackboardData.h"

AMS_DisplayStaffAIController::AMS_DisplayStaffAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/StaffAIController/ShelfStaffAIController/BehaviorTree/BP_ShelfStaffBehaviorTree"));

	MS_CHECK(BehaviorTreeObjectFinder.Object);

	BehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_DisplayStaffBlackboardData>(BehaviorTree, UMS_DisplayStaffBlackboardData::StaticClass(), TEXT("DisplayStaffBlackboardData"), RF_Transient);
	BehaviorTree->BlackboardAsset = BlackboardData;
}
