// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_WorkStaffElementWidget.h"

#include "MS_Define.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_StaffPropertyElementData.h"
#include "Table/Caches/MS_StaffCacheTable.h"

class UMS_StaffCacheTable;

void UMS_WorkStaffElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	const UMS_StaffPropertyElementData* StaffPropertyData = Cast<UMS_StaffPropertyElementData>(aListItemObject);
	if(!StaffPropertyData)
	{
		return;
	}

	
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);
	
	const FMS_Staff* StaffData = StaffTable->GetStaffData(StaffPropertyData->GetStaffId());
	if(!StaffData)
	{
		return;
	}

	if(CPP_PortraitImage)
	{
		const FString PortraitPath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StaffData->PortraitPath);
		if(UTexture2D* PortraitImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *PortraitPath)))
		{
			CPP_PortraitImage->SetBrushFromTexture(PortraitImage);
		}
	}
	
	if(CPP_StaffProfile)
	{
		CPP_StaffProfile->SetText(FText::FromString(FString::Format(TEXT("컨디션 : {0}%, 남은일 : {1}일"), {StaffPropertyData->GetCondition(), StaffPropertyData->GetWorkDay()})));
	}
}
