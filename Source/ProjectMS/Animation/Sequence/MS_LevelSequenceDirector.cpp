// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LevelSequenceDirector.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"
#include "Manager_Client/MS_PlayerCameraManager.h"

void UMS_LevelSequenceDirector::OnTrigger()
{
}

AActor* UMS_LevelSequenceDirector::GetQuarterViewCamera()
{
	if(const TObjectPtr<AMS_ViewCamera> ViewCamera = gCameraMng.GetViewCamera(EMS_ViewCameraType::QuarterView))
	{
		return Cast<AActor>(ViewCamera);
	}

	return nullptr;
}
