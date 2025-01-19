#include "AI/AIController/CustomerAIController/BehaviorTree/Task/MS_CheckWishlistStuffInStorageTask.h"

#include "Kismet/GameplayStatics.h"

#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"
#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"

UMS_CheckWishlistStuffInStorageTask::UMS_CheckWishlistStuffInStorageTask()
{
	NodeName = FString(TEXT("Check Wishlist Stuff In Storage"));
}

EBTNodeResult::Type UMS_CheckWishlistStuffInStorageTask::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UMS_CheckWishlistStuffInStorageTask::TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds)
{
	Super::TickTask(aOwnerComp, aNodeMemory, aDeltaSeconds);
	SetNextTickTime(aNodeMemory, 0.2f);

	AMS_CustomerAICharacter* OwnerCharacter = Cast<AMS_CustomerAICharacter>(aOwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("OwnerCharacter"))));
	if (OwnerCharacter == nullptr)
	{
		FinishLatentTask(aOwnerComp, EBTNodeResult::InProgress);
		return;
	}

	TArray<AActor*> AllStorageArray = {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_DisplayStorage::StaticClass(), AllStorageArray);

	struct FMS_StorageCondition
	{
		AMS_Storage* CandidateStorage = nullptr;
		FName StuffName = NAME_None;
		int UnoccupiedSlotOrder = INT_MIN;

	};

	TArray<FMS_StorageCondition> StorageConditionArray = {};

	for (int i = 0; i < AllStorageArray.Num(); i++)
	{
		AMS_DisplayStorage* Storage = Cast<AMS_DisplayStorage>(AllStorageArray[i]);
		TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatus = Storage->CheckStorageEachSlotStatus();

		for (const FMS_StorageEachSlotStatus& StorageSlotStatus : StorageEachSlotStatus)
		{
			int32* DesiredQuantity = OwnerCharacter->WishlistArray.Find(StorageSlotStatus.StuffRowName);
			if (DesiredQuantity == nullptr)
			{
				continue;
			}

			if (StorageSlotStatus.ReservationFlag == false &&
				OwnerCharacter->WishlistArray.Contains(StorageSlotStatus.StuffRowName) == true &&
				OwnerCharacter->OrderListArray.Contains(StorageSlotStatus.StuffRowName) == false &&
				*DesiredQuantity <= StorageSlotStatus.StockCapacity &&
				StorageSlotStatus.StuffRowName != NAME_None &&
				StorageSlotStatus.StockQuantity != 0
				)
			{
				FMS_StorageCondition CandidateStorageCondition = {};
				CandidateStorageCondition.CandidateStorage = Storage;
				CandidateStorageCondition.StuffName = StorageSlotStatus.StuffRowName;
				CandidateStorageCondition.UnoccupiedSlotOrder = StorageSlotStatus.SlotOrder;

				StorageConditionArray.Add(CandidateStorageCondition);
			}
		}
	}

	if (StorageConditionArray.Num() == 0)
	{
		FinishLatentTask(aOwnerComp, EBTNodeResult::InProgress);
		return;
	}

	AMS_Storage* SelectedStorage = nullptr;
	int SelectedConditionArrayIndex = INT_MIN;

	for (int i = 0; i < StorageConditionArray.Num(); i++)
	{
		if (StorageConditionArray[i].CandidateStorage->ReservedAICharacterArray.Num() == 0)
		{
			SelectedStorage = StorageConditionArray[i].CandidateStorage;
			SelectedConditionArrayIndex = i;
		}
	}

	if (SelectedStorage == nullptr)
	{
		SelectedStorage = StorageConditionArray[0].CandidateStorage;
		SelectedConditionArrayIndex = 0;
	}

	aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("TargetStorage")), SelectedStorage);
	aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("StorageBayOrder")), StorageConditionArray[SelectedConditionArrayIndex].UnoccupiedSlotOrder);
	SelectedStorage->SlotComponentArray[StorageConditionArray[SelectedConditionArrayIndex].UnoccupiedSlotOrder]->ReserveWorker(OwnerCharacter);
	SelectedStorage->AddCharacterToStorageReservationArray(OwnerCharacter);
	FinishLatentTask(aOwnerComp, EBTNodeResult::Succeeded);
}
