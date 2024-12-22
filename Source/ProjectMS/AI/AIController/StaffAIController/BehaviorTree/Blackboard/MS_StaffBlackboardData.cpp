#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Prop/Storage/MS_Prop_Storage.h"

UMS_StaffBlackboardData::UMS_StaffBlackboardData()
{
    AddEntryAsEnum(FName(TEXT("StaffIdlePattern")), TEXT("EMS_StaffIdlePattern"));
    AddEntryAsEnum(FName(TEXT("StaffObservePattern")), TEXT("EMS_StaffObservePattern"));
    AddEntryAsEnum(FName(TEXT("StaffOperatePattern")), TEXT("EMS_StaffOperatePattern"));
    AddEntryAsEnum(FName(TEXT("StaffNavigatePattern")), TEXT("EMS_StaffNavigatePattern"));

    AddEntryAsVector(FName(TEXT("TargetLocation")));
    AddEntryAsObject(FName(TEXT("TargetStorage")), AMS_Prop_Storage::StaticClass());

}