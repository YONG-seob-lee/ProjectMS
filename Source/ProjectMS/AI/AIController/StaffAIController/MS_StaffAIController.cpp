#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

#include "MS_Define.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/Blackboard/MS_StaffBlackboardComponent.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"


AMS_StaffAIController::AMS_StaffAIController()
{
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> STAFF_BEHAVIOR_TREE(TEXT("/Game/AI/AIController/BehaviorTree/BT_StaffAITree"));
	if(STAFF_BEHAVIOR_TREE.Succeeded())
	{
		StaffBehaviorTree = STAFF_BEHAVIOR_TREE.Object;
	}

	const ConstructorHelpers::FObjectFinder<UBlackboardData> STAFF_BLACK_BOARD_DATA(TEXT("/Game/AI/AIController/Blackboard/BB_StaffAIBlackboard"));
	if(STAFF_BLACK_BOARD_DATA.Succeeded())
	{
		StaffBlackboardData = STAFF_BLACK_BOARD_DATA.Object; 
	}
}

void AMS_StaffAIController::Initialize()
{
	Super::Initialize();

	if(StaffBlackboardData)
	{
		Blackboard = MS_NewObject<UMS_StaffBlackboardComponent>(this);
		if(UBlackboardComponent* BlackboardComponent = Blackboard.Get())
		{
			UseBlackboard(StaffBlackboardData, BlackboardComponent);
		}
	}
}

void AMS_StaffAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_StaffAIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_StaffAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_StaffAIController::BeginPlay()
{
	Super::BeginPlay();

	if(StaffBehaviorTree == nullptr)
	{
		return;
	}
	
	if(!RunBehaviorTree(StaffBehaviorTree))
	{
		MS_ERROR(TEXT("Warning!!! Please Check StaffBehaviorTree Instance."));
	}
}

void AMS_StaffAIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}