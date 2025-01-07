#include "AI/AIController/StaffAIController/BehaviorTree/Task/MS_ResetStaffBlackboardData.h"

UMS_ResetStaffBlackboardData::UMS_ResetStaffBlackboardData()
{
	NodeName = FString(TEXT("Reset Staff Blackboard Data"));
}

EBTNodeResult::Type UMS_ResetStaffBlackboardData::ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(aOwnerComp, aNodeMemory);

	aOwnerComp.GetBlackboardComponent()->SetValueAsString(FName(TEXT("StorageSlotStuffName")), TEXT(""));
	aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("EmptyStuffQuantity")), 0);

	aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("LoadingStorage")), nullptr);
	aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("LoadingStorageSlotOrder")), INT_MIN);
	aOwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("UnloadingStorage")), nullptr);
	aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("UnloadingStorageSlotOrder")), INT_MIN);

	aOwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("StorageBayAdjacentLocation")), FVector::ZeroVector);
	aOwnerComp.GetBlackboardComponent()->SetValueAsInt(FName(TEXT("StorageBayOrder")), INT_MIN);

	return Result;
}
