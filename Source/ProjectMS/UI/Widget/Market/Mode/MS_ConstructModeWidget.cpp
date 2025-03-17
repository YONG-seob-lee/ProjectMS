// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructModeWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Widget/Market/Expander/MS_MarketExpanderWidget.h"


void UMS_ConstructModeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(CPP_ExitButton)
	{
		CPP_ExitButton->GetOnClickedDelegate().AddUObject(this, &UMS_ConstructModeWidget::OnClickedExitButton);
	}
}

void UMS_ConstructModeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_ConstructModeWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_ConstructModeWidget::OnClickedExitButton()
{
	gItemMng.SaveFurniturePosition();
	gModeMng.ChangeState(EMS_ModeState::Normal);
}

void UMS_ConstructModeWidget::OnChangeMode(EMS_ModeState aModeState)
{
	Super::OnChangeMode(aModeState);
	
	if (CPP_ExpanderWidget)
	{
		if(aModeState == EMS_ModeState::Construct)
		{
			CPP_ExpanderWidget->OpenArrow();
		}
		else
		{
			CPP_ExpanderWidget->ResetVariable();
		}
	}
}

void UMS_ConstructModeWidget::OnCloseArrow() const
{
	if (CPP_ExpanderWidget)
	{
		CPP_ExpanderWidget->OpenArrow(false);
	}
}
