// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_PersistentWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PersistentWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Persistent"); }
};
