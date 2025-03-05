#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_ShelfStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_ShelfStorage : public AMS_Storage
{
	GENERATED_BODY()

public:
	AMS_ShelfStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds) override;
	virtual void OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds) override;

	virtual void SetVisibility(bool bVisibility) override;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* BoxSlotAttachedComponent;

	UPROPERTY()
	TMap<int32, TObjectPtr<class UMS_BoxSlotComponent>> SlotIdToBoxSlotComponents;
};
