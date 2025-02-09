#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "MS_BlackboardData.generated.h"

UCLASS(BlueprintType, Blueprintable, EditInlineNew)
class PROJECTMS_API UMS_BlackboardData : public UBlackboardData
{
	GENERATED_BODY()
	
public:
	UMS_BlackboardData();
	
public:
	void AddEntryAsMap(const FName& aEntryName);

protected:
	void AddEntryAsBool(const FName& aEntryName);
	void AddEntryAsInt(const FName& aEntryName);
	void AddEntryAsEnum(const FName& aEntryName, const FString& aEnumName);
	void AddEntryAsFloat(const FName& aEntryName);
	void AddEntryAsString(const FName& aEntryName);
	void AddEntryAsVector(const FName& aEntryName);
	void AddEntryAsRotator(const FName& aEntryName);
	void AddEntryAsObject(const FName& aEntryName, const TSubclassOf<UObject>& aObjectClass);
};
