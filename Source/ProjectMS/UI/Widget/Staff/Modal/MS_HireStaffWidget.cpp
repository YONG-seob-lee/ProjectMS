// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HireStaffWidget.h"

#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Table/RowBase/MS_Staff.h"
#include "Widget/ListViewElement/ElementData/MS_StaffProfileElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_HireStaffWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	TArray<TObjectPtr<UMS_StaffProfileElementData>> ProfileElementDatas;

	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);

	TMap<int32, FMS_Staff*> StaffDatas;
	StaffTable->GetStaffDatas(StaffDatas);
	for(const auto& StaffData : StaffDatas)
	{
		UMS_StaffProfileElementData* Data = MS_NewObject<UMS_StaffProfileElementData>(this);
		Data->SetStaffId(StaffData.Key);
		Data->SetWorkDay(FMath::RandRange(30, 120));
		ProfileElementDatas.Emplace(Data);
	}
	CPP_ProfileTileView->SetElements(TArray<UObject*>(ProfileElementDatas));
}

void UMS_HireStaffWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
