// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideAIController.h"

#include "MS_Define.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/Blackboard/MS_OutsideBlackboardComponent.h"
#include "Character/AICharacter/OutsideAICharacter/MS_MarketFrontActor.h"
#include "Character/AICharacter/OutsideAICharacter/MS_OutsideAICharacter.h"


AMS_OutsideAIController::AMS_OutsideAIController()
{
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> BEHAVIOR_TREE(TEXT("/Game/AI/AIController/BehaviorTree/BT_OutsideAITree"));
	if(BEHAVIOR_TREE.Succeeded())
	{
		OutsideBehaviorTree = BEHAVIOR_TREE.Object;
	}

	const ConstructorHelpers::FObjectFinder<UBlackboardData> BLACK_BOARD_DATA(TEXT("/Game/AI/AIController/Blackboard/BB_OutsideAIBlackboard"));
	if(BLACK_BOARD_DATA.Succeeded())
	{
		OutsideBlackboardData = BLACK_BOARD_DATA.Object; 
	}
}

void AMS_OutsideAIController::Initialize()
{
	Super::Initialize();

	if(OutsideBlackboardData)
	{
		Blackboard = MS_NewObject<UMS_OutsideBlackboardComponent>(this);
		if(UBlackboardComponent* BlackboardComponent = Blackboard.Get())
		{
			UseBlackboard(OutsideBlackboardData, BlackboardComponent);
		}

		const TObjectPtr<AMS_OutsideAICharacter> AICharacter = Cast<AMS_OutsideAICharacter>(GetCharacter());
		if(!AICharacter)
		{
			return;
		}

		const TWeakObjectPtr<AMS_MarketFrontActor> FrontActor = AICharacter->GetMarketFrontActor();
		if(FrontActor.IsValid())
		{
			Blackboard->SetValueAsObject(OutsideBoardKeyName::MarketFront, FrontActor.Get());
		}
	}
}

void AMS_OutsideAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_OutsideAIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_OutsideAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_OutsideAIController::BeginPlay()
{
	Super::BeginPlay();

	if(OutsideBehaviorTree == nullptr)
	{
		return;
	}
	
	if(!RunBehaviorTree(OutsideBehaviorTree))
	{
		MS_ERROR(TEXT("Warning!!! Please Check OutsideBehaviorTree Instance."));
	}

	// if(Blackboard)
	// {
	// 	const TObjectPtr<AMS_OutsideAICharacter> AICharacter = Cast<AMS_OutsideAICharacter>(GetCharacter());
	// 	if(!AICharacter)
	// 	{
	// 		return;
	// 	}
	//
	// 	const TWeakObjectPtr<AMS_MarketFrontActor> FrontActor = AICharacter->GetMarketFrontActor();
	// 	if(FrontActor.IsValid())
	// 	{
	// 		Blackboard->SetValueAsObject(OutsideBoardKeyName::MarketFront, FrontActor.Get());
	// 	}
	// }
}

void AMS_OutsideAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}
