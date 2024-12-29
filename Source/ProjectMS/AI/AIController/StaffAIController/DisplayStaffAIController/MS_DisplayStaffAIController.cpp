#include "AI/AIController/StaffAIController/DisplayStaffAIController/MS_DisplayStaffAIController.h"

#include "AI/AIController/StaffAIController/DisplayStaffAIController/BehaviorTree/Blackboard/MS_DisplayStaffBlackboardData.h"
#include "Actor/Character/AICharacter/StaffAICharacter/DisplayStaffAICharacter/MS_DisplayStaffAICharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Actor/Storage/MS_Storage.h"
#include "Component/Storage/MS_StorageBayComponent.h"
#include "Component/Storage/MS_StorageAssemblyAreaComponent.h"

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

	BlackboardComponent->SetValueAsEnum(FName(TEXT("AIBehaviorPattern")), 2);
	TArray<AActor*> Actors = {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_Storage::StaticClass(), Actors);
	AMS_Storage* TempStorage = nullptr;
	if (Actors.Num() > 0)
	{
		TempStorage = Cast<AMS_Storage>(Actors[0]);
		BlackboardComponent->SetValueAsEnum(FName(TEXT("AIBehvaiorPattern")), static_cast<uint8>(EMS_AIBehaviorPattern::Observe));
		BlackboardComponent->SetValueAsEnum(FName(TEXT("StaffObservePattern")), static_cast<uint8>(EMS_StaffObservePattern::Inspection));
		// BlackboardComponent->SetValueAsVector(FName(TEXT("TargetLocation")), TempStorage->StorageAssemblyAreaComponent->FindAdjacentLocationWithBay(0, StaffAICharacter));
	}
}
