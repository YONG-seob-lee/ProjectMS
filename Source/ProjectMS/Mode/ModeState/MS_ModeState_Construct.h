

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeStateBase.h"
#include "Level/MS_LevelDefine.h"
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
	// Game Input
	virtual void OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;

	virtual void OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;

	virtual void OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult) override;
	
	virtual void OnPinchAction(float aPinchValue) override;

	
	// UI Input
	UFUNCTION()
	void OnClickedStorageButton(int32 aStorageId, int32 aItemType);

	UFUNCTION()
	void OnClickApplyArrangementWidget(class UMS_ArrangementWidget* aArrangementWidget);
	
	UFUNCTION()
	void OnClickCancelArrangementWidget(class UMS_ArrangementWidget* aArrangementWidget);

	UFUNCTION()
	void OnClickRotateArrangementWidget(class UMS_ArrangementWidget* aArrangementWidget);


	// Select
	void SelectProp(AActor* aSelectedActor);
	void UnselectProp();

	UFUNCTION()
	void OnSelectProp(AActor* aSelectedActor);	// 기존의 것과 다른 Prop이 선택되야 호출됨

	UFUNCTION()
	void OnUnselectProp(AActor* aUnselectedActor);

private:
	void CreateNoLinkedPreviewProp(struct FMS_StorageData* aStorageData);
	void CreateLinkedPreviewProp(class AMS_Prop* aSelectedProp);
	
	void MovePreviewProp(const FVector& aNewLocation);
	void RotatePreviewProp();
	
	void ApplyPreviewProp();
	void CancelPreviewProp();

	FVector2d GetScreenCenterPosition() const;
	
	FVector GetLocationOnGrid(const FVector& aInLocation, bool aIsXGridCenter, bool aIsYGridCenter) const;

	bool CheckGridDatas(const TArray<const FMS_GridData*>& aGridDatas, class AMS_Prop* aTargetProp) const;
	bool CheckGridDatas(const TArray<FMS_GridDataForPropSpace>& aGridDatasForPropSpaces, class AMS_Prop* aTargetProp) const;

	void ConvertObjectDataProp(const TArray<FMS_GridDataForPropSpace>& aInGridDatas, class AMS_Prop* aInNewProp, TArray<FMS_GridDataForPropSpace>& aOutGridDatas);

	
private:
	// Member
	UPROPERTY()
	TObjectPtr<class AMS_Prop> PreviewProp;

	// Helper
	UPROPERTY()
	TObjectPtr<class UMS_GridBasedMoveHelper> GridBasedMoveHelper;

	// Delegate
	FDelegateHandle OnClickedItemButtonHandle;
};