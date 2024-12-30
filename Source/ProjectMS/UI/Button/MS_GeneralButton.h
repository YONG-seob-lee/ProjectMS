// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Button.h"
#include "MS_GeneralButton.generated.h"

UENUM()
enum class EMS_GeneralButtonType
{
	None = 0,
	Setting,
	Menu,
	Schedule,
	Manage
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_GeneralButton : public UMS_Button
{
	GENERATED_BODY()
public:
	void SetButtonType(EMS_GeneralButtonType aType);
	
	virtual void SynchronizeProperties() override;
	
private:
	void OnClickedSettingButton();
	void OnClickedMenuButton();
	void OnClickedScheduleButton();
	void OnClickedManageButton();
	
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Image = nullptr;

	UPROPERTY(EditAnywhere, Category = "ButtonType", meta = (AllowPrivateAccess = "true"))
	EMS_GeneralButtonType ButtonType = EMS_GeneralButtonType::None;
};
