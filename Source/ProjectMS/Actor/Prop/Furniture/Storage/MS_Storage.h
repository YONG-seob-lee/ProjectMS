#pragma once

#include "CoreMinimal.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "MS_Storage.generated.h"


enum class EMS_ModeState : uint8;

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
	virtual void OpenStatusWidget(const FVector2D& aClickPosition) override;
	
	virtual void OnChangeRequestSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);
	virtual void OnChangeCurrentSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* ItemSlotAttachedComponent;

	UPROPERTY()
	TMap<int32, TObjectPtr<class UMS_ItemSlotChildActorComponent>> ItemSlotIdToSlotComponents;
};