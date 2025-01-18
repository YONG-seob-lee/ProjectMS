#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_SeekUntilAvailableBayTask.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "Component/Storage/MS_StorageBayComponent.h"
#include "Component/Storage/MS_StorageAssemblyAreaComponent.h"

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

	for (int i = 0; i < TargetStorage->BayComponentArray.Num(); i++)
	{
		if (TargetStorage->BayComponentArray[i]->ReservationFlag == false && TargetStorage->BayComponentArray[i]->OccupancyFlag == false)
		{
			TargetStorage->BayComponentArray[i]->ReserveWorker(OwnerCharacter);
			aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("StorageBayOrder")), TargetStorage->BayComponentArray[i]->BayOrder);
			aOwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("StorageBayAdjacentLocation")), TargetStorage->StorageAssemblyAreaComponent->FindAdjacentLocationWithBay(TargetStorage->BayComponentArray[i]->BayOrder, OwnerCharacter));
		}
		else
		{
			FinishLatentTask(aOwnerComp, EBTNodeResult::InProgress);
			return;
		}
	}
	FinishLatentTask(aOwnerComp, EBTNodeResult::Succeeded);
}

void UMS_SeekUntilAvailableBayTask::OnMessage(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess)
{
	Super::OnMessage(aOwnerComp, aNodeMemory, aMessage, aRequestID, abSuccess);
}

void UMS_SeekUntilAvailableBayTask::OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult)
{
	Super::OnTaskFinished(aOwnerComp, aNodeMemory, aTaskResult);
}
