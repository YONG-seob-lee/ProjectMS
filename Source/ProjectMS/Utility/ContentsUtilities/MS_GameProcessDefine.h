// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_GameProcessDefine.generated.h"

/**
 * 
 */
UENUM()
enum class EMS_ControllerModeType : uint8
{
	Normal = 0,
	Rotate = 1,
};

UENUM()
enum class EMS_ModeState : uint8
{
	Normal = 0,
	Construct = 1,
	StaffManagement = 2,
	CustomerManagement = 3,
};