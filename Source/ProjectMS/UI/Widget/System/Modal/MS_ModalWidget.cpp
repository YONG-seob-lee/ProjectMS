// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModalWidget.h"

#include "MS_InModalWidget.h"
#include "Button/MS_Button.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_BlurButton)
	{
		CPP_BlurButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.ShowModalWidget(nullptr, false);
		});
	}
}

void UMS_ModalWidget::SetModal(FMS_ModalData* aModalData)
{
	CPP_InModalWidget->SetModal(aModalData);
}
