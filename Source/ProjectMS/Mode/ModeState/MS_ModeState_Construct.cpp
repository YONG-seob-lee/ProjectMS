#include "MS_ModeState_Construct.h"


UMS_ModeState_Construct::UMS_ModeState_Construct()
{
}

void UMS_ModeState_Construct::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);
}

void UMS_ModeState_Construct::Finalize()
{
	Super::Finalize();
}

void UMS_ModeState_Construct::Tick(float aDeltaTime)
{
}

void UMS_ModeState_Construct::Begin()
{
}

void UMS_ModeState_Construct::Exit()
{
}

void UMS_ModeState_Construct::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aInteractableHitResult, aSpaceHitResult);
}

void UMS_ModeState_Construct::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aInteractableHitResult, aSpaceHitResult);
}

void UMS_ModeState_Construct::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerMove(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnInputPointerHold(const FVector2D& aPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerHold(aPosition, aInteractableHitResult, aSpaceHitResult);
}

void UMS_ModeState_Construct::OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult,
	const FHitResult& aSpaceHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult, aSpaceHitResult);
}

void UMS_ModeState_Construct::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}
