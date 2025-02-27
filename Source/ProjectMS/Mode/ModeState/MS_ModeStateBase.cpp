#include "MS_ModeStateBase.h"

#include "Kismet/GameplayStatics.h"


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
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for(const auto& Actor : Actors)
	{
		if(UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Actor))
		{
			PrimitiveComponent->SetLightingChannels(false,  true, false);
		}
	}
}

void UMS_ModeStateBase::Exit()
{
}

void UMS_ModeStateBase::OnInputPointerDownEvent(FVector2D aPointerDownPosition, AActor* aHitActor)
{
}

void UMS_ModeStateBase::OnInputPointerUpEvent(FVector2D aPointerUpPosition, AActor* aHitActor)
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

void UMS_ModeStateBase::SearchPathToTarget(TArray<FIntVector2>& aOutPath, const FIntVector2& aStartPosition,
	const TArray<FIntVector2>& aTargetPositions) const
{
}
