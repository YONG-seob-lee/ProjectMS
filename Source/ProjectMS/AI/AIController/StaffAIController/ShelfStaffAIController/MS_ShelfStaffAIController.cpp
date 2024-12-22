#include "AI/AIController/StaffAIController/ShelfStaffAIController/MS_ShelfStaffAIController.h"

#include "AI/AIController/StaffAIController/ShelfStaffAIController/BehaviorTree/Blackboard/MS_ShelfStaffBlackboardData.h"

AMS_ShelfStaffAIController::AMS_ShelfStaffAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/StaffAIController/ShelfStaffAIController/BehaviorTree/BP_ShelfStaffBehaviorTree"));

	MS_CHECK(BehaviorTreeObjectFinder.Object);

	BehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_ShelfStaffBlackboardData>(BehaviorTree, UMS_ShelfStaffBlackboardData::StaticClass(), TEXT("ShelfStaffBlackboardData"), RF_Transient);
	BehaviorTree->BlackboardAsset = BlackboardData;
}
