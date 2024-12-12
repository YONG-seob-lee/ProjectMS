// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModalWidget.h"

#include "MS_InModalWidget.h"
#include "MS_WidgetManager.h"
#include "Button/MS_Button.h"

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
