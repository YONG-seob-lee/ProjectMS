#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "MS_BlackboardKeyType_Map.generated.h"

UCLASS(EditInlineNew, CollapseCategories, Blueprintable)
class PROJECTMS_API UMS_BlackboardKeyType_Map : public UBlackboardKeyType
{
	GENERATED_BODY()

public:
	UMS_BlackboardKeyType_Map();

	UFUNCTION(BlueprintCallable) void AddKeyValue(const FString& Key, UObject* Value);
	UFUNCTION(BlueprintCallable) UObject* GetValue(const FString& Key) const;
	UFUNCTION(BlueprintCallable) void RemoveKey(const FString& Key);
	UFUNCTION(BlueprintCallable) void ClearMap();

public:
	UPROPERTY(EditAnywhere, Category = "TMap") TMap<FString, UObject*> MapValue;
	UPROPERTY(EditAnywhere, Category = "TMap") FString Description = {};
};


