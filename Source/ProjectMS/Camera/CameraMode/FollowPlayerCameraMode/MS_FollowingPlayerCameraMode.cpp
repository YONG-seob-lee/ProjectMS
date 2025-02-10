#include "Camera/CameraMode/FollowingPlayerCameraMode/MS_FollowingPlayerCameraMode.h"

#include "Utility/MS_Define.h"

#include "Camera/ViewCamera/MS_ViewCamera.h"

#include "GameFramework/PlayerController.h"
#include "Manager_Client/MS_PlayerCameraManager.h"

UMS_FollowingPlayerCameraMode::UMS_FollowingPlayerCameraMode()
{
}

void UMS_FollowingPlayerCameraMode::ActivateMode()
{
	const TObjectPtr<APawn> OwnerPawn = gCameraMng.PCOwner->GetPawn();
	const TWeakObjectPtr<AMS_ViewCamera> CurrentCamera = gCameraMng.GetCurrentCamera();
	if(CurrentCamera.IsValid())
	{
		CurrentCamera->AttachToActor(OwnerPawn, FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));
	}
}

void UMS_FollowingPlayerCameraMode::DeactivateMode()
{
	const TWeakObjectPtr<AMS_ViewCamera> CurrentCamera = gCameraMng.GetCurrentCamera();
	if(CurrentCamera.IsValid())
	{
		CurrentCamera->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	}
}
