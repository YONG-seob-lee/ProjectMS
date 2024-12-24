#include "AI/AIController/StaffAIController/BehaviorTree/BehaviorTreeTask/MS_SeekUntilAvailableBayTask.h"

#include "Actor/Storage/MS_Storage.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

UMS_SeekUntilAvailableBayTask::UMS_SeekUntilAvailableBayTask()
{
	NodeName = FString(TEXT("Seek Until Available Bay"));
}

EBTNodeResult::Type UMS_SeekUntilAvailableBayTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UMS_SeekUntilAvailableBayTask::AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::AbortTask(aOwnerComp, aNodeMemory);

	return Result;
}

void UMS_SeekUntilAvailableBayTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
	SetNextTickTime(aNodeMemory, 0.75f);

	AMS_StaffAICharacter* OwnerCharacter = Cast<AMS_StaffAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	AMS_Storage* TargetStorage = Cast<AMS_Storage>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(StorageKey.SelectedKeyName));

	UE_LOG(LogTemp, Warning, TEXT("Selected key Name %s"), *StorageKey.SelectedKeyName.ToString())
}

void UMS_SeekUntilAvailableBayTask::OnMessage(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess)
{
	Super::OnMessage(aOwnerComp, aNodeMemory, aMessage, aRequestID, abSuccess);
}

void UMS_SeekUntilAvailableBayTask::OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult)
{
	Super::OnTaskFinished(aOwnerComp, aNodeMemory, aTaskResult);
}
