// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffProfileElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_StaffProfileElementData.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"

void UMS_StaffProfileElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_StaffProfileElementData> Data = Cast<UMS_StaffProfileElementData>(aListItemObject))
	{
		const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
		MS_Ensure(StaffTable);

		const FMS_Staff* StaffData = StaffTable->GetStaffData(Data->GetStaffId());

		const FString PortraitPath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StaffData->PortraitPath);
		if(UTexture2D* PortraitImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *PortraitPath)))
		{
			CPP_PortraitImage->SetBrushFromTexture(PortraitImage);
		}
		
		CPP_Name->SetText(FText::FromString(FString::Format(TEXT("이름 : {0}"), { StaffData->StaffName.ToString()})));
		const FString GenderString = ConvertEnumToString("EMS_Gender", StaffData->Gender);
		CPP_Gender->SetText(FText::FromString(FString::Format(TEXT("성별 : {0}"), {GenderString})));
		CPP_Age->SetText(FText::FromString(FString::Format(TEXT("나이 : {0}"), {StaffData->Age})));
		
		const FString MBTIString = ConvertEnumToString("EMS_MBTI", StaffData->MBTI);
		CPP_MBTI->SetText(FText::FromString(FString::Format(TEXT("MBTI : {0}"), {MBTIString})));
		CPP_RequiredSalary->SetText(FText::FromString(FString::Format(TEXT("요구 월급 : {0}"), {StaffData->RequiredSalaryMax})));
	}
}

FReply UMS_StaffProfileElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
