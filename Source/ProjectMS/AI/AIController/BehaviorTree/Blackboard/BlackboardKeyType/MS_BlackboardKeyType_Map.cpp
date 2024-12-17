#include "AI/AIController/BehaviorTree/Blackboard/BlackboardKeyType/MS_BlackboardKeyType_Map.h"

UMS_BlackboardKeyType_Map::UMS_BlackboardKeyType_Map()
{
    MapValue = TMap<FString, UObject*>();
}

void UMS_BlackboardKeyType_Map::AddKeyValue(const FString& Key, UObject* Value)
{
    if (!Key.IsEmpty() && Value)
    {
        MapValue.Add(Key, Value);
    }
}

UObject* UMS_BlackboardKeyType_Map::GetValue(const FString& Key) const
{
    if (MapValue.Contains(Key))
    {
        return MapValue[Key];
    }
    return nullptr;
}

void UMS_BlackboardKeyType_Map::RemoveKey(const FString& Key)
{
    MapValue.Remove(Key);
}

void UMS_BlackboardKeyType_Map::ClearMap()
{
    MapValue.Empty();
}