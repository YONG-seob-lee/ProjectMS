// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/NamedSlot.h"
#include "Widget/System/Toturial/MS_DescriptionWidget.h"
#include "MS_NamedSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_NamedSlot : public UNamedSlot
{
	GENERATED_BODY()
public:

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	EMS_TutorialDirection Direction = EMS_TutorialDirection::DownToRight; 
};
