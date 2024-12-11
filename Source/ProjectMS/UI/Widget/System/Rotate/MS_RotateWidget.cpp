#include "MS_RotateWidget.h"

#include "Button/MS_Button.h"

void UMS_RotateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_RotateButtonLeft)
	{
		CPP_RotateButtonLeft->GetOnClickedDelegate().AddUObject(this, &UMS_RotateWidget::OnClockedLeftRotateButton);
	}

	if(CPP_RotateButtonRight)
	{
		CPP_RotateButtonRight->GetOnClickedDelegate().AddUObject(this, &UMS_RotateWidget::OnClickedRightRotateButton);
	}

	if(CPP_ReturnRotateButton)
	{
		CPP_ReturnRotateButton->GetOnClickedDelegate().AddUObject(this, &UMS_RotateWidget::OnClickedReturnRotateButton);
	}
}

void UMS_RotateWidget::OnClockedLeftRotateButton()
{
}

void UMS_RotateWidget::OnClickedRightRotateButton()
{
}

void UMS_RotateWidget::OnClickedReturnRotateButton()
{
}
