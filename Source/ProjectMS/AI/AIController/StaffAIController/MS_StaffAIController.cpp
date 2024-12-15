#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

#include "AI/AIController/StaffAIController/Blackboard/MS_StaffBlackboardData.h"

AMS_StaffAIController::AMS_StaffAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/StaffAIController/BehaviorTree/BP_StaffBehaviorTree"));
	MS_CHECK(BehaviorTreeObjectFinder.Object);

	BehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_StaffBlackboardData>(BehaviorTree, UMS_StaffBlackboardData::StaticClass(), TEXT("BP_StaffBlackboardData"), RF_Transient);
	BehaviorTree->BlackboardAsset = BlackboardData;
}

void AMS_StaffAIController::BeginPlay()
{
	Super::BeginPlay();

	ExecuteBehaviorTree();
}
