#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

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

	StaffAICharacter = Cast<AMS_StaffAICharacter>(GetPawn());
	ExecuteBehaviorTree();
	if (BlackboardComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BlackboardComponent is nullptr %s"), *GetName());
	}
	else
	{
		BlackboardComponent->SetValueAsEnum(FName(TEXT("AIBehaviorPattern")), static_cast<uint8>(EMS_AIBehaviorPattern::Idle));
		UE_LOG(LogTemp, Warning, TEXT("BlackboardComponent is not nullptr"));
	}
}

void AMS_StaffAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}
