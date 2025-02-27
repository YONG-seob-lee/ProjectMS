// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_WorkStaffListWidget.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_StaffPropertyElementData.h"
#include "Widget/WidgetComponent/MS_ListView.h"

void UMS_WorkStaffListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<UMS_StaffPropertyElementData*> StaffPropertys;
	gItemMng.GetStaffProperties(StaffPropertys);
	
	CPP_WorkStaffProfileTileView->SetListItems(TArray<UObject*>(StaffPropertys));
}

void UMS_WorkStaffListWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
