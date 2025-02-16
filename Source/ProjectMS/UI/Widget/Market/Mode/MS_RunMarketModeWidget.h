// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeWidget.h"
#include "MS_RunMarketModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_RunMarketModeWidget : public UMS_ModeWidget
{
	GENERATED_BODY()

public:
	static FName GetWidgetName() { return TEXT("RunMarket"); }

	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void OnChangeMode(EMS_ModeState aModeState) override;
};
