#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"

#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "AI/AIController/CustomerAIController/BehaviorTree/Blackboard/MS_CustomerBlackboardData.h"

AMS_CustomerAIController::AMS_CustomerAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/CustomerAIController/BehaviorTree/BP_CustomerAIBehaviorTree"));

	MS_CHECK(BehaviorTreeObjectFinder.Object);

	BehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_CustomerBlackboardData>(BehaviorTree, UMS_CustomerBlackboardData::StaticClass(), TEXT("CustomerBlackboardData"), RF_Transient);
	BehaviorTree->BlackboardAsset = BlackboardData;
}

void AMS_CustomerAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_CustomerAIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_CustomerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_CustomerAIController::BeginPlay()
{
	Super::BeginPlay();

	CustomerAICharacter = Cast<AMS_CustomerAICharacter>(GetPawn());
	ExecuteBehaviorTree();

	BlackboardComponent->SetValueAsEnum(FName(TEXT("AIBehaviorPattern")), static_cast<uint8>(EMS_AIBehaviorPattern::Idle));
}

void AMS_CustomerAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}
