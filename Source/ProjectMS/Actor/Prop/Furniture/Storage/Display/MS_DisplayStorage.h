#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_DisplayStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_DisplayStorage : public AMS_Storage
{
	GENERATED_BODY()

public:
	AMS_DisplayStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void OnChangeRequestSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas) override;
	virtual void OnChangeCurrentSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas) override;

	virtual void SetVisibility(bool bVisibility) override;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ItemSlotAttachedComponent;

	UPROPERTY()
	TMap<int32, TObjectPtr<class UMS_ItemSlotChildActorComponent>> SlotIdToItemSlotComponents;
};
