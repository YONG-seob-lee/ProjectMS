// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SetDisplaysAsSearchTargetsAITask.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"
#include "Algo/RandomShuffle.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StorageUnit.h"

UMS_SetDisplaysAsSearchTargetsAITask::UMS_SetDisplaysAsSearchTargetsAITask(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Set Displays As Search Targets";
	bNotifyTick = false;
}

EBTNodeResult::Type UMS_SetDisplaysAsSearchTargetsAITask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	if (static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction)) != EMS_CustomerActionType::PickUpItems)
	{
		return EBTNodeResult::Type::Failed;
	}

	TArray<TWeakObjectPtr<UMS_UnitBase>> Units;
	gUnitMng.GetUnits(EMS_UnitType::Storage, Units);

	TArray<FIntVector2> TargetPositions = {};
		
	TArray<TWeakObjectPtr<UMS_StorageUnit>> DisplayUnits = {};
	TArray<TWeakObjectPtr<UMS_StorageUnit>> IncludeWannaItemDisplayUnits = {};
	
	for (const TWeakObjectPtr<UMS_UnitBase>& Unit : Units)
	{
		const TWeakObjectPtr<UMS_StorageUnit> StorageUnit = Cast<UMS_StorageUnit>(Unit);
		if (StorageUnit == nullptr)
		{
			MS_ENSURE(false);
			continue;
		}

		if(StorageUnit->GetZoneType() != EMS_ZoneType::Display)
		{
			continue;
		}
		// AITest 나중에 모든 아이템이 전부 픽업 되면 바로 카운터로 이동할 수 있게 개선.
		if(AIUnit->IsVisitBefore(StorageUnit->GetUnitHandle()))
		{
			continue;
		}

		// 손님이 원하는 아이템 목록
		TMap<int32, int32> RemainItems;
		AIUnit->GetRemainItems(RemainItems);
		TArray<int32> RemainItemIds;
		RemainItems.GenerateKeyArray(RemainItemIds);

		// 손님이 원하는 아이템이 들어있는 스토리지 따로 저장.
		if(StorageUnit->HasItemInStorage(RemainItemIds))
		{
			IncludeWannaItemDisplayUnits.Emplace(StorageUnit);
		}
		
		DisplayUnits.Emplace(StorageUnit);
	}

	// 이번 테스크때 원하는 아이템을 구해야할지 말아야 할 지
	const bool bIsCustomerPickUpWannaItem = BlackboardComp->GetValueAsBool(CustomerBoardKeyName::IsCustomerPickUpWannaItem);

	// 선정할 매대 인덱스 ( 손님이 원하는 종류의 아이템이 포함되어있는 매대만 표시 )

	TWeakObjectPtr<UMS_StorageUnit> TargetStorage = nullptr;
	if(bIsCustomerPickUpWannaItem)
	{
		if(IncludeWannaItemDisplayUnits.IsValidIndex(0))
		{
			TargetStorage = IncludeWannaItemDisplayUnits[0];
		}
	}
	else
	{
		
		TArray<int32> RandomNum;

		for(int32 i = 0 ; i < DisplayUnits.Num(); i++)
		{
			RandomNum.Emplace(i);
		}
		Algo::RandomShuffle(RandomNum);

		int32 TargetNumber = 0;
		for(int32 i = 0 ; i < RandomNum.Num(); i++)
		{
			if(IncludeWannaItemDisplayUnits.Contains(DisplayUnits[i]) == false)
			{
				TargetNumber = i;
				break;
			}
		}
		
		if(RandomNum.IsValidIndex(TargetNumber))
		{
			if(DisplayUnits.IsValidIndex(RandomNum[TargetNumber]))
			{
				TargetStorage = DisplayUnits[RandomNum[TargetNumber]];
			}	
		}
	}
	

	// 해당 매대를 찾는 구간.
	const TArray<UMS_PropSpaceComponent*>& PropPurposeSpaceComponents = TargetStorage->GetPropPurposeSpaceComponents(EMS_PurposeType::UseStorage);

	if (PropPurposeSpaceComponents.Num() == 0)
	{
		return EBTNodeResult::Type::Failed;
	}
			
	for (const UMS_PropSpaceComponent* PurposeSpaceComponent : PropPurposeSpaceComponents)
	{
		TargetPositions.Emplace(PurposeSpaceComponent->GetCenterGridPosition());
	}

	AIUnit->AddVisitStorageUnitHandle(TargetStorage->GetUnitHandle());
	
	AIUnit->SetTargetPositions(TargetPositions);
	return TargetPositions.IsEmpty() ? EBTNodeResult::Type::Failed : EBTNodeResult::Type::Succeeded;
}
