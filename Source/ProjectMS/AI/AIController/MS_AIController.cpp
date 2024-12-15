#include "AI/AIController/MS_AIController.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "AI/AIController/BehaviorTree/Blackboard/MS_BlackboardData.h"
#include "AI/AIController/BehaviorTree/Blackboard/BlackboardKeyType/MS_BlackboardKeyTypeMap.h"

AMS_AIController::AMS_AIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/BehaviorTree/BP_AIBehaviorTree"));
	MS_CHECK(BehaviorTreeObjectFinder.Object);

	DefaultBehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_BlackboardData>(DefaultBehaviorTree, UMS_BlackboardData::StaticClass(), TEXT("BP_AIBehaviorTree"), RF_Transient);
	DefaultBehaviorTree->BlackboardAsset = BlackboardData;
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
	RunBehaviorTree(DefaultBehaviorTree);
    BlackboardComponent = GetBlackboardComponent();
    BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(GetBrainComponent());

	SynchronizeBlackboard();
    SynchronizeSubBehaviorTreeToBlackboard();
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

void AMS_AIController::SynchronizeSubBehaviorTreeToBlackboard()
{
    FName MapKeyName(TEXT("SubBehaviorTreeMap"));
    if (!BlackboardData->Keys.ContainsByPredicate([&](const FBlackboardEntry& aEntry) { return aEntry.EntryName == MapKeyName; }))
    {
        UMS_BlackboardData* CustomBlackboardData = Cast<UMS_BlackboardData>(BlackboardData);
        if (CustomBlackboardData)
        {
            CustomBlackboardData->AddEntryAsMap(MapKeyName);
        }
    }

    UMS_BlackboardKeyTypeMap* MapKeyType = nullptr;
    for (const auto& Entry : BlackboardData->Keys)
    {
        if (Entry.EntryName == MapKeyName)
        {
            MapKeyType = Cast<UMS_BlackboardKeyTypeMap>(Entry.KeyType);
            break;
        }
    }

    MapKeyType->ClearMap();

    for (const auto& Pair : SubBehaviorTreeMap)
    {
        MapKeyType->AddKeyValue(Pair.Key, Pair.Value);
    }
}