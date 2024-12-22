#include "AI/AIController/MS_AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "AI/AIController/BehaviorTree/Blackboard/MS_BlackboardData.h"

AMS_AIController::AMS_AIController()
{
	// BehaviorTree Initialization Procedure

	/*
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/BehaviorTree/BP_AIBehaviorTree"));
	MS_CHECK(BehaviorTreeObjectFinder.Object);

	BehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_BlackboardData>(BehaviorTree, UMS_BlackboardData::StaticClass(), TEXT("BP_AIBehaviorTree"), RF_Transient);
	BehaviorTree->BlackboardAsset = BlackboardData;
	*/
}

void AMS_AIController::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AMS_AIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_AIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}

void AMS_AIController::ExecuteBehaviorTree()
{
	MS_CHECK(BehaviorTree);

	RunBehaviorTree(BehaviorTree);
    BlackboardComponent = GetBlackboardComponent();
    BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(GetBrainComponent());

	SynchronizeBlackboard();
}

void AMS_AIController::TerminateBehaviorTree()
{
	if (BehaviorTreeComponent->IsValidLowLevel() == true)
	{
		BehaviorTreeComponent->StopLogic(FString(TEXT("")));
	}
}

void AMS_AIController::SynchronizeBlackboard()
{
	BlackboardComponent->SetValueAsObject(FName(TEXT("OwnerCharacter")), GetPawn());
	BlackboardComponent->SetValueAsObject(FName(TEXT("OwnerController")), this);
}
