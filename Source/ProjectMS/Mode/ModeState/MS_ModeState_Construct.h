

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
	virtual void OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult, const FHitResult& aSpaceHitResult) override;
	
	virtual void OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult, const FHitResult& aSpaceHitResult) override;
	
	virtual void OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;
	
	virtual void OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend) override;

	virtual void OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult, const FHitResult& aSpaceHitResult) override;

	virtual void OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult, const FHitResult& aSpaceHitResult) override;
	
	virtual void OnPinchAction(float aPinchValue) override;
};
