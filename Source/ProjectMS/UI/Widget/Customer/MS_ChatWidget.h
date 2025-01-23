// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modal/MS_CustomerManagementWidget.h"
#include "Widget/MS_Widget.h"
#include "MS_ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ChatWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetChat(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ChatEntryWidget> CPP_ChatEntry = nullptr;
};
