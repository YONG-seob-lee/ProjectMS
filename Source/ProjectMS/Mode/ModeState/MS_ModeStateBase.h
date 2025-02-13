

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/MS_StateBase.h"
#include "MS_ModeStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeStateBase : public UMS_StateBase
{
	GENERATED_BODY()
	
public:
	UMS_ModeStateBase();

	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;

protected:
	virtual void Begin() override;
	virtual void Exit() override;

public:
	UFUNCTION()
	virtual void OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult);
	
	UFUNCTION()
	virtual void OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult);

	UFUNCTION()
	virtual void OnInputPointerGlidingUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult);
	
	UFUNCTION()
	virtual void OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend);

	UFUNCTION()
	virtual void OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend);

	UFUNCTION()
	virtual void OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta, const FVector2D& aPositionDeltaTrend);

	UFUNCTION()
	virtual void OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult);

	UFUNCTION()
	virtual void OnInputPointerLongTouch(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult);
	
	UFUNCTION()
	virtual void OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult);

	UFUNCTION()
	virtual void OnInputPointerDoubleClickEvent(FVector2D aPosition, const FHitResult& aInteractableHitResult);
	
	UFUNCTION()
	virtual void OnPinchAction(float aPinchValue);
};
