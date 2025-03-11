// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffProfileElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_StaffProfileElementData.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Widget/Staff/MS_StaffDetailWidget.h"

void UMS_StaffProfileElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_StaffProfileElementData> Data = Cast<UMS_StaffProfileElementData>(aListItemObject))
	{
		SetProfile(Data->GetStaffId(), Data->GetWorkDay());
	}
}

void UMS_StaffProfileElementWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffDetailWidget::GetWidgetName());
	Parameter.bPlayOpenAnimation = false;
	Parameter.bPlayCloseAnimation = false;

	if(const TObjectPtr<UMS_StaffDetailWidget> StaffDetailWidget = Cast<UMS_StaffDetailWidget>(Parameter.InModalWidget))
	{
		StaffDetailWidget->SetDetail(StaffId, WorkDay);
	}
	gWidgetMng.ShowModalWidget(Parameter);
}

FReply UMS_StaffProfileElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// FMS_ModalParameter Parameter;
	// Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffDetailWidget::GetWidgetName());
	// Parameter.bPlayOpenAnimation = false;
	// Parameter.bPlayCloseAnimation = false;
	//
	// if(const TObjectPtr<UMS_StaffDetailWidget> StaffDetailWidget = Cast<UMS_StaffDetailWidget>(Parameter.InModalWidget))
	// {
	// 	StaffDetailWidget->SetDetail(StaffId, WorkDay);
	// }
	// gWidgetMng.ShowModalWidget(Parameter);
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UMS_StaffProfileElementWidget::SetProfile(int32 aStaffId, int32 aWorkDay)
{
	StaffId = aStaffId;
	WorkDay = aWorkDay;
	
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);
	
	const FMS_Staff* StaffData = StaffTable->GetStaffData(aStaffId);

	const FString PortraitPath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StaffData->PortraitPath);
	if(UTexture2D* PortraitImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *PortraitPath)))
	{
		CPP_PortraitImage->SetBrushFromTexture(PortraitImage);
	}
	
	CPP_Name->SetText(FText::FromString(FString::Format(TEXT("이름 : {0}"), { FText::FromStringTable(MS_LocalizedTableId::StringTable, StaffData->StaffNameLocalKey).ToString()})));
	const FString GenderString = ConvertEnumToString("EMS_Gender", StaffData->Gender);
	CPP_Gender->SetText(FText::FromString(FString::Format(TEXT("성별 : {0}"), {GenderString})));
	CPP_Age->SetText(FText::FromString(FString::Format(TEXT("나이 : {0}(오리나이)"), {StaffData->Age})));
		
	const FString MBTIString = ConvertEnumToString("EMS_MBTI", StaffData->MBTI);
	CPP_MBTI->SetText(FText::FromString(FString::Format(TEXT("MBTI : {0}"), {MBTIString})));
	CPP_WorkDay->SetText(FText::FromString(FString::Format(TEXT("근무 일수 : {0}일"), {WorkDay})));
	CPP_RequiredSalary->SetText(FText::FromString(FString::Format(TEXT("요구 월급 : {0}Gold"), {StaffData->RequiredSalaryMax})));
}
