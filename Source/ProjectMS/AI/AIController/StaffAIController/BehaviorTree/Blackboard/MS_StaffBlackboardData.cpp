#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

UMS_StaffBlackboardData::UMS_StaffBlackboardData()
{
    AddEntryAsEnum(FName(TEXT("StaffObservePattern")), TEXT("EMS_StaffObservePattern"));
    AddEntryAsEnum(FName(TEXT("StaffOperatePattern")), TEXT("EMS_StaffOperatePattern"));
    AddEntryAsEnum(FName(TEXT("StaffInteractPattern")), TEXT("EMS_StaffInteractPattern"));
    AddEntryAsEnum(FName(TEXT("StaffIdlePattern")), TEXT("EMS_StaffIdlePattern"));

    AddEntryAsString(FName(TEXT("StorageSlotStuffName")));
    AddEntryAsInt(FName(TEXT("EmptyStuffQuantity")));

    AddEntryAsObject(FName(TEXT("LoadingStorage")), AMS_Storage::StaticClass());
    AddEntryAsInt(FName(TEXT("LoadingStorageSlotOrder")));
    AddEntryAsObject(FName(TEXT("UnloadingStorage")), AMS_Storage::StaticClass());
    AddEntryAsInt(FName(TEXT("UnloadingStorageSlotOrder")));

    AddEntryAsVector(FName(TEXT("StorageBayAdjacentLocation")));
    AddEntryAsInt(FName(TEXT("StorageBayOrder")));
}