﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_HireStaffWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_HireStaffWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("HireStaff"); }

	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_ProfileTileView = nullptr;
};
