// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_AIDefine.generated.h"

UENUM()
enum class EMS_IssueType
{
	None = 0,
	Payment = 1,
	RemoveItemsFromDisplay = 2,
	AddItemsToDisplay = 3,
	RemoveItemsFromShelf = 4,
	AddItemsToShelf = 5,
};