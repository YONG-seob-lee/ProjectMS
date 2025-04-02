// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerShoppingLoopBTDecorator.h"

#include "MS_UnitBase.h"
#include "AI/AIController/MS_AIController.h"
#include "Algo/RandomShuffle.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTCompositeNode.h"
#include "BehaviorTree/Composites/BTComposite_SimpleParallel.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_StorageUnit.h"

struct FMS_BTLoopDecoratorMemory
{
	int32 SearchId;
	uint8 RemainingExecutions;
	double TimeStarted;
};

UMS_CustomerShoppingLoopBTDecorator::UMS_CustomerShoppingLoopBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Customer Shopping Loop";
	INIT_DECORATOR_NODE_NOTIFY_FLAGS();

	bInitialize = false;
	bCreateNodeInstance = true;
	ShoppingNumLoops = 0;
	RealFindItemIndex.Empty();
}

void UMS_CustomerShoppingLoopBTDecorator::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	FMS_BTLoopDecoratorMemory* DecoratorMemory = GetNodeMemory<FMS_BTLoopDecoratorMemory>(SearchData);
	FBTCompositeMemory* ParentMemory = GetParentNode()->GetNodeMemory<FBTCompositeMemory>(SearchData);
	const bool bIsSpecialNode = GetParentNode()->IsA(UBTComposite_SimpleParallel::StaticClass());

	if ((bIsSpecialNode && ParentMemory->CurrentChild == BTSpecialChild::NotInitialized) ||
		(!bIsSpecialNode && ParentMemory->CurrentChild != ChildIndex))
	{
		// initialize counter if it's first activation
		const int32 TotalShoppingNumLoops = GetShoppingNumLoops();
		SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsInt(CustomerBoardKeyName::CustomerLoopCount, TotalShoppingNumLoops);
		DecoratorMemory->RemainingExecutions = IntCastChecked<uint8>(TotalShoppingNumLoops);
		DecoratorMemory->TimeStarted = GetWorld()->GetTimeSeconds();
		bInitialize = true;
	}

	bool bShouldLoop = false;
	if (DecoratorMemory->RemainingExecutions > 0)
	{
		SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsInt(CustomerBoardKeyName::CustomerLoopCount, DecoratorMemory->RemainingExecutions);
		
		if(RealFindItemIndex.Contains(DecoratorMemory->RemainingExecutions))
		{
			SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsBool(CustomerBoardKeyName::IsCustomerPickUpWannaItem, true);
		}
		else
		{
			SearchData.OwnerComp.GetBlackboardComponent()->SetValueAsBool(CustomerBoardKeyName::IsCustomerPickUpWannaItem, false);
		}
		
		DecoratorMemory->RemainingExecutions--;
	}
	bShouldLoop = DecoratorMemory->RemainingExecutions > 0;

	// set child selection overrides
	if (bShouldLoop)
	{
		GetParentNode()->SetChildOverride(SearchData, ChildIndex);
	}
}

void UMS_CustomerShoppingLoopBTDecorator::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	Super::OnNodeDeactivation(SearchData, NodeResult);

	FMS_BTLoopDecoratorMemory* DecoratorMemory = GetNodeMemory<FMS_BTLoopDecoratorMemory>(SearchData);
	if(DecoratorMemory->RemainingExecutions <= 0)
	{
		bInitialize = false;
		ShoppingNumLoops = 0;
		RealFindItemIndex.Empty();
	}
}

FString UMS_CustomerShoppingLoopBTDecorator::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %d loops"), *Super::GetStaticDescription(), ShoppingNumLoops);
}

void UMS_CustomerShoppingLoopBTDecorator::DescribeRuntimeValues(const UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, EBTDescriptionVerbosity::Type Verbosity, TArray<FString>& Values) const
{
	Super::DescribeRuntimeValues(OwnerComp, NodeMemory, Verbosity, Values);

	const FMS_BTLoopDecoratorMemory* DecoratorMemory = reinterpret_cast<FMS_BTLoopDecoratorMemory*>(NodeMemory);
	Values.Add(FString::Printf(TEXT("loops remaining: %d"), DecoratorMemory->RemainingExecutions));
}

void UMS_CustomerShoppingLoopBTDecorator::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FMS_BTLoopDecoratorMemory>(NodeMemory, InitType);
}

void UMS_CustomerShoppingLoopBTDecorator::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FMS_BTLoopDecoratorMemory>(NodeMemory, CleanupType);
}

bool UMS_CustomerShoppingLoopBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return EBTNodeResult::Type::Failed;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return EBTNodeResult::Type::Failed;
	}
		
	const TObjectPtr<UMS_CustomerAIAnimInstance> AIAnimInstance = Cast<UMS_CustomerAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
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

	const FMS_BTLoopDecoratorMemory* DecoratorMemory = reinterpret_cast<FMS_BTLoopDecoratorMemory*>(NodeMemory);
	if(DecoratorMemory->TimeStarted <= 0)
	{
		return true;
	}
	
	BlackboardComp->SetValueAsInt(CustomerBoardKeyName::WannaItemCount, AIUnit->GetWannaItemCount());
	BlackboardComp->SetValueAsInt(CustomerBoardKeyName::PickUpItemCount, AIUnit->GetPickUpItemCount());
	
	if(AIUnit->IsPickUpAllItems() || DecoratorMemory->RemainingExecutions <= 0)
	{
		const EMS_CustomerActionType CustomerActionType = static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction));

		if(CustomerActionType == EMS_CustomerActionType::Payment || CustomerActionType == EMS_CustomerActionType::GoHome ||
			CustomerActionType == EMS_CustomerActionType::AngryAndGoHome)
		{
			return false;
		}
		
		AIUnit->UnregisterCustomerAction(CustomerActionType);

		BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerAction, static_cast<uint8>(EMS_CustomerActionType::None));
		BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerActionState, static_cast<uint8>(EMS_CustomerActionState::None));
		AIAnimInstance->SetActionState(EMS_CustomerActionState::None);
		
		return EBTNodeResult::Type::Failed;
	}
	
	return true;
}

uint16 UMS_CustomerShoppingLoopBTDecorator::GetInstanceMemorySize() const
{
	return sizeof(FMS_BTLoopDecoratorMemory);
}

int32 UMS_CustomerShoppingLoopBTDecorator::GetShoppingNumLoops()
{
	ShoppingNumLoops = 0;
	if(const TObjectPtr UnitManager = gUnitMng)
	{
		TArray<TWeakObjectPtr<UMS_UnitBase>> Units;
		UnitManager->GetUnits(EMS_UnitType::Storage, Units);

		for(const auto& Unit : Units)
		{
			if(const TObjectPtr<UMS_StorageUnit> StorageUnit = Cast<UMS_StorageUnit>(Unit))
			{
				if(StorageUnit->GetZoneType() == EMS_ZoneType::Display)
				{
					++ShoppingNumLoops;
				}
			}
		}
	}

	constexpr int32 MinLoop = 3;

	// 루프 횟수 정하기.
	if(ShoppingNumLoops > 9)
	{
		ShoppingNumLoops = FMath::RandRange(MinLoop, 9);
	}
	else
	{
		ShoppingNumLoops = FMath::RandRange(MinLoop, ShoppingNumLoops);
	}

	// 셔플
	TArray<int32> Numbers;
	for(int32 i = 1; i <= ShoppingNumLoops; i++)
	{
		Numbers.Add(i);
	}

	Algo::RandomShuffle(Numbers);
	if(Numbers.IsValidIndex(0))
	{
		RealFindItemIndex.Emplace(Numbers[0]);
	}
	if(Numbers.IsValidIndex(1))
	{
		RealFindItemIndex.Emplace(Numbers[1]);
	}
	if(Numbers.IsValidIndex(2))
    {
    	RealFindItemIndex.Emplace(Numbers[2]);
    }
	
	return ShoppingNumLoops;
}
