// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HireStaffWidget.h"

#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Widget/ListViewElement/ElementData/MS_StaffProfileElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_HireStaffWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	TArray<TObjectPtr<UMS_StaffProfileElementData>> ProfileElementDatas;
	gItemMng.GetStaffProfileElementData(ProfileElementDatas);
	CPP_ProfileTileView->SetElements(TArray<UObject*>(ProfileElementDatas));
}

void UMS_HireStaffWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
