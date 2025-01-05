

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeStateBase.h"
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


	void SelectProp(AActor* aSelectedActor);
	void UnselectProp();

	UFUNCTION()
	void OnSelectProp(AActor* aSelectedActor);

	UFUNCTION()
	void OnUnselectProp(AActor* aUnselectedActor);
	
	void CreatePreviewProp(class AMS_Prop* aSelectedProp);
	void MovePreviewProp(const FVector& NewLocation);
	void ApplyPreviewProp();
	void CancelPreviewProp(class AMS_Prop* aSelectedProp);

	bool GetHitResultUnderObjectScreenPosition(const FVector2D& aPointerPostion, ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const;
	
private:
	TObjectPtr<class AMS_Prop> SelectedPreviewProp;

	FVector2D PointerPostionToObjectScreenPositionOffset;
};
