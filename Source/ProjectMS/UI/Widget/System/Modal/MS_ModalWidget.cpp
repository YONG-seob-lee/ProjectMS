// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModalWidget.h"

#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
	if(CPP_BlurButton)
	{
		CPP_BlurButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.ShowModalWidget(nullptr, false);
		});
	}
}

void UMS_ModalWidget::SetModal(const TObjectPtr<UMS_Widget>& aNewWidget)
{
	CPP_InModalPanel->ClearChildren();
	
	CPP_InModalPanel->AddChild(aNewWidget);
}
