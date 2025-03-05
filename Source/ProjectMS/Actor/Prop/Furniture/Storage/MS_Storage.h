#pragma once

#include "CoreMinimal.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "MS_Storage.generated.h"


UCLASS()
class PROJECTMS_API AMS_Storage : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Storage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;


public:
	// Slot Datas
	virtual TWeakObjectPtr<class UMS_Widget> OpenStatusWidget() override;
	
	virtual void OnChangeRequestSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds);
	virtual void OnChangeCurrentSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds);

	virtual void SetVisibility(bool bVisibility) override;
};