#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"

AMS_StaffAIController::AMS_StaffAIController()
{
}

void AMS_StaffAIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_StaffAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_StaffAIController::BeginPlay()
{
	Super::BeginPlay();

	ExecuteBehaviorTree();
}

void AMS_StaffAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}
