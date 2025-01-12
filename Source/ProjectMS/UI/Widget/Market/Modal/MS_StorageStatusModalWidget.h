// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_StorageStatusModalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageStatusModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/Market/Modal/StorageStatusModalWidget.StorageStatusModalWidget"));}
	
private:
	
};
