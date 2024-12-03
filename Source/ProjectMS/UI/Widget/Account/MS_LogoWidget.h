// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_LogoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LogoWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bActivate) override;
	virtual void FinishWidget() override;

	virtual void OnAnimFinished(const FName& aAnimName) override;
};
