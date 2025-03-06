// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_IsCustomerTakeAllWannaItemBTDecorator.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/Market/Customer/MS_CustomerAIAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "Units/MS_CustomerAIUnit.h"

UMS_IsCustomerTakeAllWannaItemBTDecorator::UMS_IsCustomerTakeAllWannaItemBTDecorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Customer Take All Wanna Buy Items";
}

bool UMS_IsCustomerTakeAllWannaItemBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const TObjectPtr<AMS_AIController> AIController = Cast<AMS_AIController>(OwnerComp.GetAIOwner());
	if(!AIController)
	{
		return false;
	}

	const TObjectPtr<AMS_MarketAICharacter> AICharacter = Cast<AMS_MarketAICharacter>(AIController->GetCharacter());
	if(!AICharacter)
	{
		return false;
	}

	
	const TObjectPtr<UMS_CustomerAIUnit> AIUnit = Cast<UMS_CustomerAIUnit>(AICharacter->GetOwnerUnitBase());
	if(!AIUnit)
	{
		return false;
	}

	const TObjectPtr<UMS_CustomerAIAnimInstance> AIAnimInstance = Cast<UMS_CustomerAIAnimInstance>(AICharacter->GetAIAnimInstance());
	if(!AIAnimInstance)
	{
		return false;
	}

	const TObjectPtr<UBlackboardComponent> BlackboardComp = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent());
	if(!BlackboardComp)
	{
		return false;
	}

	
	if(BlackboardComp->GetValueAsBool(CustomerBoardKeyName::IsCustomerPickUpAllItem) == true)
	{
		// 만약 원하는 아이템 종류중 하나라도 구하지 못했다면?( 구했는데 아이템 갯수가 적은건 결제 )
		if(AIUnit->IsExceptAnyWannaItem())
		{
			// 불쾌함을 표시하며 물건을 전부 내려놓고 바로 마켓바깥으로 나가기
		}
		else
		{
			// 결제하기
			return true;
		}
	}
	
	return true;
}
