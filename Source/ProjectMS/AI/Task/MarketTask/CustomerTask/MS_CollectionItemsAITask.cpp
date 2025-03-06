// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CollectionItemsAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StorageUnit.h"

UMS_CollectionItemsAITask::UMS_CollectionItemsAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "CollectionItemsAITask";
	bNotifyTick = true;
}

EBTNodeResult::Type UMS_CollectionItemsAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const TObjectPtr<AMS_CustomerAIController> AIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_CustomerAICharacter> AICharacter = Cast<AMS_CustomerAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return EBTNodeResult::Type::Failed;
	}

	if(AIUnit->GetPath().IsEmpty() == false || AIUnit->GetTargetPositions().IsEmpty() == false)
	{
		return EBTNodeResult::Type::Failed;
	}
	
	// 유닛이 필요로 하는 아이템을 수집하는 행위
	TMap<int32, int32> RemainItems;
	AIUnit->GetRemainItems(RemainItems);

	if(RemainItems.IsEmpty())
	{
		return EBTNodeResult::Type::Succeeded;
	}

	bool bPickUpAnyItem = false;
	for(const auto& RemainItem : RemainItems)
	{
		// 현재 위치해있는 디스플레이 유닛을 찾는 행위
		UMS_UnitBase* Unit = gUnitMng.GetUnit(AIUnit->GetTargetStorageUnitHandle());
		if(!Unit)
		{
			return EBTNodeResult::Type::Failed;
		}

		if(UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(Unit))
		{
			// AITest 나중에 가구 스토리지에 있는 아이템과 대조하여 맞춰야함.
			const int32 SubtractItemCount = StorageUnit->SubtractAnySlotCurrentItemCount(RemainItem.Key, RemainItem.Value, false);

			if(SubtractItemCount > 0)
			{
				AIUnit->EventBehavior(EMS_BehaviorType::PickUpItem);
				AIUnit->PickUpItem(RemainItem.Key, SubtractItemCount);
				bPickUpAnyItem = true;
			}
		}
	}

	ChattingType = EMS_ChattingType::Undefined;
	if(bPickUpAnyItem == false)
	{
		ChattingType = EMS_ChattingType::ThereIsNoItem;
	}

	AIUnit->ResetChatting();
	// AITest 나중에 해당 스토리지에서 PickUp 해갈 아이템 총합과 비례하게 ConsiderTime 을 입력해야함.
	ConsiderProcessTime = 0.f;
	ConsiderTime = 3.f;
	return EBTNodeResult::Type::InProgress;
}

void UMS_CollectionItemsAITask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(ConsiderProcessTime > ConsiderTime)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	ConsiderProcessTime += DeltaSeconds;

	const TObjectPtr<AMS_CustomerAIController> AIController = Cast<AMS_CustomerAIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return;
	}

	const TObjectPtr<AMS_CustomerAICharacter> AICharacter = Cast<AMS_CustomerAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		
		return;
	}

	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return;
	}

	if(AIUnit->IsChatBefore() == false)
	{
		AIUnit->EventChatting(ChattingType);
	}
}
