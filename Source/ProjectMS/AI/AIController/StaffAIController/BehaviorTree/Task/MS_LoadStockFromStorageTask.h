#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"
#include "MS_LoadStockFromStorageTask.generated.h"

UCLASS() class PROJECTMS_API UMS_LoadStockFromStorageTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_LoadStockFromStorageTask();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

	// Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FBlackboardKeySelector TargetStorageKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_SlotStaticMeshType SlotStaticMeshType = {};
};
