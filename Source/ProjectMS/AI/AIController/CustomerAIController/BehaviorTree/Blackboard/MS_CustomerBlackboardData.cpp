#include "AI/AIController/CustomerAIController/BehaviorTree/Blackboard/MS_CustomerBlackboardData.h"

#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

UMS_CustomerBlackboardData::UMS_CustomerBlackboardData()
{
	AddEntryAsEnum(FName(TEXT("CustomerObservePattern")), TEXT("EMS_CustomerObservePattern"));
	AddEntryAsEnum(FName(TEXT("CustomerOperatePattern")), TEXT("EMS_CustomerOperatePattern"));
	AddEntryAsEnum(FName(TEXT("CustomerInteractPattern")), TEXT("EMS_CustomerInteractPattern"));
	AddEntryAsEnum(FName(TEXT("CustomerIdlePattern")), TEXT("EMS_CustomerIdlePattern"));

    AddEntryAsObject(FName(TEXT("TargetStorage")), AMS_Storage::StaticClass());
	AddEntryAsVector(FName(TEXT("StorageBayAdjacentLocation")));
	AddEntryAsInt(FName(TEXT("StorageBayOrder")));
}
