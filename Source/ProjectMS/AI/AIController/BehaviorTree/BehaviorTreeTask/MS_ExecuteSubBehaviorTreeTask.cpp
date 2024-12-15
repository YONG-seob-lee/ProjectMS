#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_ExecuteSubBehaviorTreeTask.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTree.h"

#include "AI/AIController/BehaviorTree/Blackboard/BlackboardKeyType/MS_BlackboardKeyTypeMap.h"

UMS_ExecuteSubBehaviorTreeTask::UMS_ExecuteSubBehaviorTreeTask()
{
	NodeName = FString(TEXT("Execute SubTree"));
    bNotifyTick = true;
}

EBTNodeResult::Type UMS_ExecuteSubBehaviorTreeTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (BlackboardComponent == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    if (SubBehaviorTreeKey.SelectedKeyName.IsValid() == false)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardData* BlackboardData = BlackboardComponent->GetBlackboardAsset();
    if (BlackboardData == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UMS_BlackboardKeyTypeMap* MapKeyType = nullptr;

    for (const FBlackboardEntry& Entry : BlackboardData->Keys)
    {
        if (Entry.EntryName == SubBehaviorTreeKey.SelectedKeyName)
        {
            MapKeyType = Cast<UMS_BlackboardKeyTypeMap>(Entry.KeyType);
            break;
        }
    }

    if (MapKeyType == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UObject* BehaviorTreeObject = MapKeyType->GetValue(BehaviorTreeName);
    SubBehaviorTree = Cast<UBehaviorTree>(BehaviorTreeObject);

    if (SubBehaviorTree == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    OwnerComp.StartTree(*SubBehaviorTree, EBTExecutionMode::Looped);
    IsSubBehaviorTreeRunning = true;

    return EBTNodeResult::InProgress;
}


EBTNodeResult::Type UMS_ExecuteSubBehaviorTreeTask::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(OwnerComp, NodeMemory);

	return Result;
}

void UMS_ExecuteSubBehaviorTreeTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    if (IsSubBehaviorTreeRunning == false)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    bool SubBehaviorTreeCondition = OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("SubBehaviorTreeCondition"));

    if (SubBehaviorTreeCondition)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        IsSubBehaviorTreeRunning = false;
    }
}

void UMS_ExecuteSubBehaviorTreeTask::OnMessage(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, FName Message, int32 RequestID, bool bSuccess)
{
	Super::OnMessage(OwnerComp, NodeMemory, Message, RequestID, bSuccess);
}

void UMS_ExecuteSubBehaviorTreeTask::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
