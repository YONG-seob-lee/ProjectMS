#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_PalletStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_PalletStorage : public AMS_Storage
{
	GENERATED_BODY()
	
public:
	AMS_PalletStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds) override;
	virtual void OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds) override;

	virtual void SetVisibility(bool bVisibility) override;

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMS_StackedBoxComponent> StackedBoxComponent;
};
