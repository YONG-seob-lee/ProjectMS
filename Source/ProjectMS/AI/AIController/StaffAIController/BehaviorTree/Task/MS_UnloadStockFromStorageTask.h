#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "Component/Storage/MS_StorageSlotComponent.h"
#include "MS_UnloadStockFromStorageTask.generated.h"

UCLASS() class PROJECTMS_API UMS_UnloadStockFromStorageTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_UnloadStockFromStorageTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

	// Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FBlackboardKeySelector TargetStorageKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_SlotStaticMeshType SlotStaticMeshType = {};
};
