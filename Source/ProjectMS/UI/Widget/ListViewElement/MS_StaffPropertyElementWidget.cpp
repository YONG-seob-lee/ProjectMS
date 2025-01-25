// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffPropertyElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_StaffPropertyElementData.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Widget/Staff/MS_StaffDetailWidget.h"

void UMS_StaffPropertyElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	const UMS_StaffPropertyElementData* StaffPropertyData = Cast<UMS_StaffPropertyElementData>(aListItemObject);
	if(!StaffPropertyData)
	{
		return;
	}
	
	StaffId = StaffPropertyData->GetStaffId();
	
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);
	
	const FMS_Staff* StaffData = StaffTable->GetStaffData(StaffId);

	const FString PortraitPath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StaffData->PortraitPath);
	if(UTexture2D* PortraitImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *PortraitPath)))
	{
		CPP_PortraitImage->SetBrushFromTexture(PortraitImage);
	}

	CPP_Name->SetText(FText::FromString(FString::Format(TEXT("이름 : {0}"), {StaffData->StaffName.ToString()})));
	CPP_HP->SetText(FText::FromString(FString::Format(TEXT("체력 : {0}"), {StaffPropertyData->GetHP()})));
	CPP_Condition->SetText(FText::FromString(FString::Format(TEXT("컨디션 : {0}"), {StaffPropertyData->GetCondition()})));
	CPP_Feeling->SetText(FText::FromString(FString::Format(TEXT("기분 : {0}"), {0})));
	CPP_ExpirationDate->SetText(FText::FromString(FString::Format(TEXT("만료일 : {0}월 {1}일"), {StaffPropertyData->GetExpirationMonth(), StaffPropertyData->GetExpirationDay()})));
}

FReply UMS_StaffPropertyElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffDetailWidget::GetWidgetName());
	Parameter.bPlayOpenAnimation = false;
	Parameter.bPlayCloseAnimation = false;

	if(const TObjectPtr<UMS_StaffDetailWidget> StaffDetailWidget = Cast<UMS_StaffDetailWidget>(Parameter.InModalWidget))
	{
		StaffDetailWidget->SetDetail(StaffId);
		StaffDetailWidget->ShowButtonPanel(false);
	}
	gWidgetMng.ShowModalWidget(Parameter);
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
