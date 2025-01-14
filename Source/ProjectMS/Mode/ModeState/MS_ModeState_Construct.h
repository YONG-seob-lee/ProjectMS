

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeStateBase.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_ModeState_Construct.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeState_Construct : public UMS_ModeStateBase
{
	GENERATED_BODY()
	
public:
	UMS_ModeState_Construct();

	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;

public:
	virtual void OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;

	virtual void OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;

	virtual void OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnPinchAction(float aPinchValue) override;

	UFUNCTION()
	void OnClickedStorageButton(int32 aStorageId, int32 aItemType);
	
	void SelectProp(AActor* aSelectedActor);
	void UnselectProp();

	UFUNCTION()
	void OnSelectProp(AActor* aSelectedActor);	// 기존의 것과 다른 Prop이 선택되야 호출됨

	UFUNCTION()
	void OnUnselectProp(AActor* aUnselectedActor);

	void OnClickApplyPreviewProp(class UMS_PreviewWidget* aPreviewWidget);
	void OnClickCancelPreviewProp(class UMS_PreviewWidget* aPreviewWidget);

	void CreateNoLinkedPreviewProp(struct FMS_StorageData* aStorageData);
	void CreateLinkedPreviewProp(class AMS_Prop* aSelectedProp);
	
	void MovePreviewProp(const FVector& aNewLocation);
	void ApplyPreviewProp();
	void CancelPreviewProp(class AMS_Prop* aSelectedProp);

	void ShowPreviewWidget(bool bShow);

	FVector2d GetScreenCenterPosition() const;
	bool GetHitResultUnderObjectScreenPosition(const FVector2D& aPointerPostion, ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const;

private:
	FIntVector GetGridPosition(const FVector& aInLocation, bool aIsXGridCenter, bool aIsYGridCenter, bool aIsZGridCenter = false) const;
	
	FVector GetLocationOnGrid(const FVector& aInLocation, bool aIsXGridCenter, bool aIsYGridCenter, bool aIsZGridCenter = false) const;

	bool CheckGridDatas(const TArray<const FMS_GridData*>& aGridDatas, class AMS_Prop* aTargetProp) const;
	bool CheckGridDatas(const TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces, class AMS_Prop* aTargetProp) const;

	void ConvertObjectDataProp(const TArray<FMS_GridDataForPropSpace>& aInGridDatas, class AMS_Prop* aInNewProp, TArray<FMS_GridDataForPropSpace>& aOutGridDatas);

	
private:
	TObjectPtr<class AMS_Prop> SelectedPreviewProp;

	FVector2D PointerPostionToObjectScreenPositionOffset;

	FDelegateHandle OnClickedItemButtonHandle;
};
