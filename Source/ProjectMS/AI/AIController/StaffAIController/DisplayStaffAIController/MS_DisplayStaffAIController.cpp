#include "AI/AIController/StaffAIController/DisplayStaffAIController/MS_DisplayStaffAIController.h"

#include "AI/AIController/StaffAIController/DisplayStaffAIController/BehaviorTree/Blackboard/MS_DisplayStaffBlackboardData.h"
#include "Actor/Character/AICharacter/StaffAICharacter/DisplayStaffAICharacter/MS_DisplayStaffAICharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "Component/Prop/Furniture/MS_StorageBayComponent.h"
#include "Component/Prop/Furniture/MS_StorageAssemblyAreaComponent.h"

AMS_DisplayStaffAIController::AMS_DisplayStaffAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeObjectFinder(TEXT("/Game/AI/AIController/StaffAIController/DisplayStaffAIController/BehaviorTree/BP_DisplayStaffBehaviorTree"));

	MS_CHECK(BehaviorTreeObjectFinder.Object);

	BehaviorTree = BehaviorTreeObjectFinder.Object;
	BlackboardData = NewObject<UMS_DisplayStaffBlackboardData>(BehaviorTree, UMS_DisplayStaffBlackboardData::StaticClass(), TEXT("DisplayStaffBlackboardData"), RF_Transient);
	BehaviorTree->BlackboardAsset = BlackboardData;
}

void AMS_DisplayStaffAIController::BeginPlay()
{
	Super::BeginPlay();
}
