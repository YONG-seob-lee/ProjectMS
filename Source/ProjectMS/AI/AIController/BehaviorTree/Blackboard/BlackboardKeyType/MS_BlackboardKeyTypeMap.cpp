#include "AI/AIController/BehaviorTree/Blackboard/BlackboardKeyType/MS_BlackboardKeyTypeMap.h"

UMS_BlackboardKeyTypeMap::UMS_BlackboardKeyTypeMap()
{
    MapValue = TMap<FString, UObject*>();
}

void UMS_BlackboardKeyTypeMap::AddKeyValue(const FString& Key, UObject* Value)
{
    if (!Key.IsEmpty() && Value)
    {
        MapValue.Add(Key, Value);
    }
}

UObject* UMS_BlackboardKeyTypeMap::GetValue(const FString& Key) const
{
    if (MapValue.Contains(Key))
    {
        return MapValue[Key];
    }
    return nullptr;
}

void UMS_BlackboardKeyTypeMap::RemoveKey(const FString& Key)
{
    MapValue.Remove(Key);
}

void UMS_BlackboardKeyTypeMap::ClearMap()
{
    MapValue.Empty();
}