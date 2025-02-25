#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"

#include "MS_Define.h"
#include "AI/Blackboard/MS_CustomerBlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AMS_CustomerAIController::AMS_CustomerAIController()
{
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> CUSTOMER_BEHAVIOR_TREE(TEXT("/Game/AI/AIController/BehaviorTree/BT_CustomerAITree"));
	if(CUSTOMER_BEHAVIOR_TREE.Succeeded())
	{
		CustomerBehaviorTree = CUSTOMER_BEHAVIOR_TREE.Object;
	}

	const ConstructorHelpers::FObjectFinder<UBlackboardData> CUSTOMER_BLACK_BOARD_DATA(TEXT("/Game/AI/AIController/Blackboard/BB_CustomerAIBlackboard"));
	if(CUSTOMER_BLACK_BOARD_DATA.Succeeded())
	{
		CustomerBlackboardData = CUSTOMER_BLACK_BOARD_DATA.Object; 
	}
}

void AMS_CustomerAIController::Initialize()
{
	Super::Initialize();
	
	if(CustomerBlackboardData)
	{
		Blackboard = MS_NewObject<UMS_CustomerBlackboardComponent>(this);
		if(UBlackboardComponent* BlackboardComponent = Blackboard.Get())
		{
			UseBlackboard(CustomerBlackboardData, BlackboardComponent);
		}
	}

	ReadyToMarket();
}

void AMS_CustomerAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_CustomerAIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_CustomerAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_CustomerAIController::BeginPlay()
{
	Super::BeginPlay();

	if(CustomerBehaviorTree == nullptr)
	{
		return;
	}
	
	if(!RunBehaviorTree(CustomerBehaviorTree))
	{
		MS_ERROR(TEXT("Warning!!! Please Check CustomerBehaviorTree Instance."));
	}
}

void AMS_CustomerAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}

void AMS_CustomerAIController::ReadyToMarket() const
{
	Blackboard->SetValueAsEnum(StaffBoardKeyName::CurrentActionProcess, static_cast<uint8>(EMS_CustomerActionState::MoveUsingSpline));
}
