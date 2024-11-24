#include "Camera/Public/CameraMode/FollowingPlayerCameraMode/MS_FollowingPlayerCameraMode.h"

#include "Utility/MS_Define.h"

#include "Management/Public/MS_PlayerCameraManager.h"
#include "Camera/Public/ViewCamera/MS_ViewCamera.h"

#include "GameFramework/PlayerController.h"

UMS_FollowingPlayerCameraMode::UMS_FollowingPlayerCameraMode()
{
}

void UMS_FollowingPlayerCameraMode::ActivateMode()
{
	CameraManager = Cast<AMS_PlayerCameraManager>(GetOuter());
	MS_CHECK(CameraManager);

	CameraManager->ViewCamera->AttachToActor(CameraManager->PCOwner->GetPawn(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false));
}

void UMS_FollowingPlayerCameraMode::DeactivateMode()
{
	CameraManager->ViewCamera->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}
