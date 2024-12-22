#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "MS_MoveToLocationTask.generated.h"

UCLASS(Meta = (DisplayName = "Move To Location Task"), HideCategories = ("Node")) class PROJECTMS_API UMS_MoveToLocationTask : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UMS_MoveToLocationTask();

	virtual FString GetStaticDescription() const override;
};
