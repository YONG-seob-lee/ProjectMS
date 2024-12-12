// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_InModalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_InModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	void SetModal(struct FMS_ModalData* AModalData);
};
