#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

AMS_StaffAIController::AMS_StaffAIController()
{
}

void AMS_StaffAIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);

	StaffAICharacter = Cast<AMS_StaffAICharacter>(GetPawn());

	ExecuteBehaviorTree();
	BlackboardComponent->SetValueAsEnum(FName(TEXT("AIBehaviorPattern")), static_cast<uint8>(EMS_AIBehaviorPattern::Idle));
}

void AMS_StaffAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_StaffAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}
