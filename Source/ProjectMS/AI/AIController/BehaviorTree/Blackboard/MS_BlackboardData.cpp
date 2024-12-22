#include "AI/AIController/BehaviorTree/Blackboard/MS_BlackboardData.h"

#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "AI/AIController/MS_AIController.h"

#include "AI/AIController/BehaviorTree/Blackboard/BlackboardKeyType/MS_BlackboardKeyType_Map.h"

UMS_BlackboardData::UMS_BlackboardData()
{
    AddEntryAsObject(FName(TEXT("OwnerCharacter")), AMS_AICharacter::StaticClass());
    AddEntryAsObject(FName(TEXT("OwnerController")), AMS_AIController::StaticClass());
    AddEntryAsEnum(FName("AIBehaviorPattern"), TEXT("EMS_AIBehaviorPattern"));
}

void UMS_BlackboardData::AddEntryAsBool(const FName& aEntryName)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Bool>(aEntryName);
    UBlackboardKeyType_Bool* BoolKeyType = Cast<UBlackboardKeyType_Bool>(BlackboardEntry.KeyType);
    BoolKeyType->bDefaultValue = false;
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsInt(const FName& aEntryName)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Int>(aEntryName);
    UBlackboardKeyType_Int* IntKeyType = Cast<UBlackboardKeyType_Int>(BlackboardEntry.KeyType);
    IntKeyType->DefaultValue = INT_MIN;
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsEnum(const FName& aEntryName, const FString& aEnumName)
{
    if (aEntryName.IsNone() == true || aEnumName.IsEmpty() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Enum>(aEntryName);

    UBlackboardKeyType_Enum* EnumKeyType = Cast<UBlackboardKeyType_Enum>(BlackboardEntry.KeyType);
    EnumKeyType->EnumName = aEnumName;
    EnumKeyType->EnumType = UClass::TryFindTypeSlow<UEnum>(FString(TEXT("/Script/")) + FString(FApp::GetProjectName()) + FString(TEXT(".")) + aEnumName, EFindFirstObjectOptions::ExactClass);
    EnumKeyType->bIsEnumNameValid = false;

    if (EnumKeyType->EnumType != nullptr)
    {
        Keys.Add(BlackboardEntry);
    }
    else
    {
        BlackboardEntry.KeyType->ConditionalBeginDestroy();
    }
}

void UMS_BlackboardData::AddEntryAsFloat(const FName& aEntryName)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Float>(aEntryName);
    UBlackboardKeyType_Float* FloatKeyType = Cast<UBlackboardKeyType_Float>(BlackboardEntry.KeyType);
    FloatKeyType->DefaultValue = -FLT_MAX;
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsString(const FName& aEntryName)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_String>(aEntryName);
    UBlackboardKeyType_String* StringKeyType = Cast<UBlackboardKeyType_String>(BlackboardEntry.KeyType);
    StringKeyType->DefaultValue = FString();
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsVector(const FName& aEntryName)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Vector>(aEntryName);
    UBlackboardKeyType_Vector* VectorKeyType = Cast<UBlackboardKeyType_Vector>(BlackboardEntry.KeyType);
    VectorKeyType->bUseDefaultValue = true;
    VectorKeyType->DefaultValue = FVector::ZeroVector;
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsRotator(const FName& aEntryName)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Rotator>(aEntryName);
    UBlackboardKeyType_Rotator* RotatorKeyType = Cast<UBlackboardKeyType_Rotator>(BlackboardEntry.KeyType);
    RotatorKeyType->bUseDefaultValue = true;
    RotatorKeyType->DefaultValue = FRotator::ZeroRotator;
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsObject(const FName& aEntryName, const TSubclassOf<UObject>& aObjectClass)
{
    if (aEntryName.IsNone() == true)
    {
        return;
    }

    FBlackboardEntry BlackboardEntry = {};
    BlackboardEntry.EntryName = aEntryName;
    BlackboardEntry.KeyType = CreateDefaultSubobject<UBlackboardKeyType_Object>(aEntryName);
    UBlackboardKeyType_Object* ObjectKeyType = Cast<UBlackboardKeyType_Object>(BlackboardEntry.KeyType);
    ObjectKeyType->BaseClass = aObjectClass;
    Keys.Add(BlackboardEntry);
}

void UMS_BlackboardData::AddEntryAsMap(const FName& EntryName)
{
    if (EntryName.IsNone())
    {
        return;
    }

    FBlackboardEntry BlackboardEntry;
    BlackboardEntry.EntryName = EntryName;

    BlackboardEntry.KeyType = NewObject<UMS_BlackboardKeyType_Map>(this, UMS_BlackboardKeyType_Map::StaticClass(), FName(*FString::Printf(TEXT("BlackboardKeyType_%s"), *EntryName.ToString())));
    if (BlackboardEntry.KeyType)
    {
        Keys.Add(BlackboardEntry);
    }
}
