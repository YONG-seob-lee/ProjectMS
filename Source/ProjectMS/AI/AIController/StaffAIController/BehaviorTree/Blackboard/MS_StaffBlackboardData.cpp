#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Storage/MS_Storage.h"

UMS_StaffBlackboardData::UMS_StaffBlackboardData()
{
    AddEntryAsEnum(FName(TEXT("StaffObservePattern")), TEXT("EMS_StaffObservePattern"));
    AddEntryAsEnum(FName(TEXT("StaffOperatePattern")), TEXT("EMS_StaffOperatePattern"));
    AddEntryAsEnum(FName(TEXT("StaffInteractPattern")), TEXT("EMS_StaffInteractPattern"));
    AddEntryAsEnum(FName(TEXT("StaffIdlePattern")), TEXT("EMS_StaffIdlePattern"));

    AddEntryAsObject(FName(TEXT("LoadingStorage")), AMS_Storage::StaticClass());
    AddEntryAsInt(FName(TEXT("LoadingStorageSlotOrder")));

    AddEntryAsObject(FName(TEXT("UnloadingStorage")), AMS_Storage::StaticClass());
    AddEntryAsInt(FName(TEXT("UnloadingStorageSlotOrder")));
    // SlotOrder로 어디 슬롯 체크할지 저장해놓음

    AddEntryAsString(FName(TEXT("StorageSlotStuffName")));
    // 재고이름은 한개로 충분

    // 아래 내용은 바꿔가면서 사용
    AddEntryAsVector(FName(TEXT("StorageBayAdjacentLocation")));
    AddEntryAsInt(FName(TEXT("StorageBayOrder")));
    AddEntryAsInt(FName(TEXT("StorageSlotStockCapacity")));
    AddEntryAsInt(FName(TEXT("StorageSlotStockQuantity")));
}