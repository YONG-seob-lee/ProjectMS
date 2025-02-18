#include "MS_ModeStateBase.h"


UMS_ModeStateBase::UMS_ModeStateBase()
{
	
}

void UMS_ModeStateBase::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);
}

void UMS_ModeStateBase::Finalize()
{
	Super::Finalize();
}

void UMS_ModeStateBase::Tick(float aDeltaTime)
{
}

void UMS_ModeStateBase::Begin()
{
}

void UMS_ModeStateBase::Exit()
{
}

void UMS_ModeStateBase::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnInputPointerGlidingUpEvent(FVector2D aPointerUpPosition,
	const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
}

void UMS_ModeStateBase::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
}

void UMS_ModeStateBase::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
}

void UMS_ModeStateBase::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnInputPointerLongTouch(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnInputPointerDoubleClickEvent(FVector2D aPosition, const FHitResult& aInteractableHitResult)
{
}

void UMS_ModeStateBase::OnPinchAction(float aPinchValue)
{
}

void UMS_ModeStateBase::SearchPathToTargetOrGate(TArray<FIntVector2>& aOutPath, bool& bOutSearchGate, const FIntVector2& aStartPosition,
	const TArray<FIntVector2>& aTargetPositions) const
{
}
