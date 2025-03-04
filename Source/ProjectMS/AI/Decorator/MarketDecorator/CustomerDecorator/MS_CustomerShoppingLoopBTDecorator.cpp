// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerShoppingLoopBTDecorator.h"

#include "MS_UnitBase.h"
#include "AI/AIController/MS_AIController.h"
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


	if(const TObjectPtr UnitManager = gUnitMng)
	{
		ShoppingNumLoops = 0;
		TArray<TObjectPtr<UMS_UnitBase>> Units;
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
		DecoratorMemory->RemainingExecutions = IntCastChecked<uint8>(ShoppingNumLoops);
		DecoratorMemory->TimeStarted = GetWorld()->GetTimeSeconds();
	}

	bool bShouldLoop = false;
	if (DecoratorMemory->RemainingExecutions > 0)
	{
		DecoratorMemory->RemainingExecutions--;
	}
	bShouldLoop = DecoratorMemory->RemainingExecutions > 0;

	// set child selection overrides
	if (bShouldLoop)
	{
		GetParentNode()->SetChildOverride(SearchData, ChildIndex);
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
	
	if(DecoratorMemory->RemainingExecutions <= 0)
	{
		if(BlackboardComp->GetValueAsBool(CustomerBoardKeyName::CustomerPickUpAllItem) == true)
		{
			return false;
		}

		const EMS_CustomerActionType CustomerActionType = static_cast<EMS_CustomerActionType>(BlackboardComp->GetValueAsEnum(CustomerBoardKeyName::CustomerAction));
		AIUnit->UnregisterCustomerAction(CustomerActionType);

		BlackboardComp->SetValueAsBool(CustomerBoardKeyName::CustomerPickUpAllItem, true);
		BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerAction, static_cast<uint8>(EMS_CustomerActionType::None));
		BlackboardComp->SetValueAsEnum(CustomerBoardKeyName::CustomerActionState, static_cast<uint8>(EMS_CustomerActionState::None));
		AIAnimInstance->SetActionState(EMS_CustomerActionState::None);
	}
	
	return true;
}

uint16 UMS_CustomerShoppingLoopBTDecorator::GetInstanceMemorySize() const
{
	return sizeof(FMS_BTLoopDecoratorMemory);
}
