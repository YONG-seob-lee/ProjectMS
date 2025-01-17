// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageStatusWidget.h"

#include "MS_Define.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_StorageStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//CPP_TileView->SetElements()
	CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_StorageStatusWidget::OnClickedConfirmButton);
}

void UMS_StorageStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_StorageStatusWidget::OnClickedConfirmButton()
{
	gWidgetMng.DestroyWidget(UMS_StorageStatusWidget::GetWidgetName());
}
