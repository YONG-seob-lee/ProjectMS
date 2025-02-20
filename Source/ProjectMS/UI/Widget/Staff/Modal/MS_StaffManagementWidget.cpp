// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffManagementWidget.h"

#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/ListViewElement/ElementData/MS_StaffPropertyElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_StaffManagementWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	TArray<UMS_StaffPropertyElementData*> StaffPropertys;
	gItemMng.GetStaffProperties(StaffPropertys);

	if(StaffPropertys.Num() == 0)
	{
		CPP_ProfileSwitcher->SetActiveWidgetIndex(0);
	}
	else
	{
		CPP_ProfileSwitcher->SetActiveWidgetIndex(1);
		CPP_ProfileTileView->SetElements(TArray<UObject*>(StaffPropertys));
	}
}

void UMS_StaffManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_StaffManagementWidget::NativeDestruct()
{
	gWidgetMng.DestroyWidget(GetWidgetName());
	Super::NativeDestruct();
}
