// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SceneCommand.h"

#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "PlayerState/MS_PlayerState.h"

void UMS_SceneCommand::SetLevelType(EMS_LevelType aType, const UWorld* aWorld /* = nullptr */)
{
	if(aType == EMS_LevelType::LobbyLevel)
	{
		CheckTownLevelType(LevelType, aWorld);
		ReplaceCamera(LevelType);
		return;
	}
	
	ReplaceCamera(aType);
	LevelType = aType;
}

void UMS_SceneCommand::SetPreviousLevelType(EMS_LevelType aType, const UWorld* aWorld /* = nullptr */)
{
	if(aType == EMS_LevelType::LobbyLevel)
	{
		CheckTownLevelType(PreviousLevelType, aWorld);
		return;
	}
	PreviousLevelType = aType;
}

void UMS_SceneCommand::SetCreateFrom(const ANSICHAR* File, const int32 Line)
{
	const FString FileName = FPaths::GetCleanFilename(ANSI_TO_TCHAR(File));
	const FString FileLine = FString::Format(TEXT("{0}({1})"), { FileName, Line} );
	CreateFileLine = FileLine;
}

void UMS_SceneCommand::CheckTownLevelType(EMS_LevelType& aLevelType, const UWorld* aWorld /* = nullptr */)
{
	if (!IsValid(aWorld))
	{
		return;
	}

	const AMS_PlayerController* PlayerController = aWorld->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	const AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}

	const int32 OpenedZoneCount = PlayerState->GetOpenedZoneCount();
	if(OpenedZoneCount < static_cast<int32>(EMS_TownBoundary::Stage2))
	{
		aLevelType = EMS_LevelType::Stage01;
	}
	else
	{
		if(OpenedZoneCount < static_cast<int32>(EMS_TownBoundary::Stage3))
		{
			aLevelType = EMS_LevelType::Stage02;
		}
		else
		{
			aLevelType = EMS_LevelType::Stage03;
		}
	}
}

void UMS_SceneCommand::ReplaceCamera(EMS_LevelType aType)
{
	gCameraMng.ReplaceCamera(aType);
}
