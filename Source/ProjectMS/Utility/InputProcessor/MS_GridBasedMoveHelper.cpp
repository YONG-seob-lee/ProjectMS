#include "MS_GridBasedMoveHelper.h"

#include "MS_Define.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Manager_Client/MS_InputManager.h"


class AMS_PlayerController;

UMS_GridBasedMoveHelper::UMS_GridBasedMoveHelper()
	: TargetActor(nullptr), PointerPostionToObjectScreenPositionOffset(FVector2D::ZeroVector)
{
}

const FVector2D& UMS_GridBasedMoveHelper::SetPositionOffset(AActor* aTargetActor)
{
	UWorld* World = GetWorld();
	if (!IsValid(World) || !IsValid(aTargetActor))
	{
		TargetActor = nullptr;
		PointerPostionToObjectScreenPositionOffset = FVector2D::ZeroVector;
		return PointerPostionToObjectScreenPositionOffset;
	}

	TargetActor = aTargetActor;
	
	FVector2D PointerScreenPosition = gInputMng.AcquirePointerPositionOnViewport();
	MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::PointerScreenPosition : %f, %f"), PointerScreenPosition.X, PointerScreenPosition.Y);

	FVector2D ActorCenterScreenPosition;
	World->GetFirstPlayerController()->ProjectWorldLocationToScreen(aTargetActor->GetActorLocation(), ActorCenterScreenPosition);
	MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::ActorCenterScreenPosition : %f, %f"), ActorCenterScreenPosition.X, ActorCenterScreenPosition.Y);
		
	PointerPostionToObjectScreenPositionOffset = ActorCenterScreenPosition - PointerScreenPosition;
	MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::ClickPositionToObjectScreenPositionOffset : %f, %f"), PointerPostionToObjectScreenPositionOffset.X, PointerPostionToObjectScreenPositionOffset.Y);

	return PointerPostionToObjectScreenPositionOffset;
}

void UMS_GridBasedMoveHelper::ResetPositionOffset()
{
	TargetActor = nullptr;
	PointerPostionToObjectScreenPositionOffset = FVector2D::ZeroVector;
}

bool UMS_GridBasedMoveHelper::GetHitResultUnderObjectScreenPosition(const FVector2D& aPointerPostion,
                                                                    ECollisionChannel aTraceChannel, bool bTraceComplex, FHitResult& aOutHitResult) const
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return false;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!IsValid(PlayerController))
	{
		return false;
	}

	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::aPointerPostion : %f, %f"), aPointerPostion.X, aPointerPostion.Y);

	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::PointerPostionToObjectScreenPositionOffset : %f, %f"), PointerPostionToObjectScreenPositionOffset.X, PointerPostionToObjectScreenPositionOffset.Y);

	FVector2D ScreenPosition = aPointerPostion + PointerPostionToObjectScreenPositionOffset;
	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::ScreenPosition : %f, %f"), ScreenPosition.X, ScreenPosition.Y);
		
	return PlayerController->GetHitResultAtScreenPosition(ScreenPosition, aTraceChannel, bTraceComplex, aOutHitResult);
}

bool UMS_GridBasedMoveHelper::GetCheckedHitResultUnderObjectScreenPosition(AActor* aTargetActor,
	const FVector2D& aPointerPostion, ECollisionChannel aTraceChannel, bool bTraceComplex,
	FHitResult& aOutHitResult) const
{
	MS_Ensure (aTargetActor == TargetActor);

	return GetHitResultUnderObjectScreenPosition(aPointerPostion, aTraceChannel, bTraceComplex, aOutHitResult);
}
