// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffPropertyElementWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "ElementData/MS_StaffPropertyElementData.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Widget/Staff/MS_StaffDetailWidget.h"

void UMS_StaffPropertyElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);
	UMS_StaffPropertyElementData* StaffPropertyData = Cast<UMS_StaffPropertyElementData>(aListItemObject);
	if(!StaffPropertyData)
	{
		return;
	}
	
	StaffId = StaffPropertyData->GetStaffId();
	WorkDay = StaffPropertyData->GetWorkDay();
	
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);
	
	const FMS_Staff* StaffData = StaffTable->GetStaffData(StaffId);

	const FString PortraitPath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, StaffData->PortraitPath);
	if(UTexture2D* PortraitImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *PortraitPath)))
	{
		CPP_PortraitImage->SetBrushFromTexture(PortraitImage);
	}

	if(CPP_StaffIssueBox)
	{
		for(int32 i = static_cast<int32>(EMS_StaffIssueType::None) ; i < static_cast<int32>(EMS_StaffIssueType::AddItemsToShelf); i++)
		{
			const FString IssueName = GetIssueName(i);
			CPP_StaffIssueBox->AddOption(IssueName);
			SelectItems.Emplace(i, IssueName);
		}

		CPP_StaffIssueBox->OnSelectionChanged.AddUniqueDynamic(this, &UMS_StaffPropertyElementWidget::OnSelectChanged);
	}
	
	CPP_Name->SetText(FText::FromString(FString::Format(TEXT("이름 : {0}"), {StaffData->StaffName.ToString()})));
	CPP_HP->SetText(FText::FromString(FString::Format(TEXT("체력 : {0}"), {StaffPropertyData->GetHP()})));
	CPP_Condition->SetText(FText::FromString(FString::Format(TEXT("컨디션 : {0}"), {StaffPropertyData->GetCondition()})));
	CPP_Feeling->SetText(FText::FromString(FString::Format(TEXT("기분 : {0}"), {0})));
	CPP_ExpirationDate->SetText(FText::FromString(FString::Format(TEXT("만료일 : {0}월 {1}일"), {StaffPropertyData->GetExpirationDate().Month, StaffPropertyData->GetExpirationDate().Day})));
	
	if(CPP_BlurPanel)
	{
		const FMS_GameDate GameDate = gScheduleMng.GetGameDate();
		if(GameDate < StaffPropertyData->GetFirstDateOfWork())
		{
			CPP_BlurPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CPP_BlurPanel->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

FReply UMS_StaffPropertyElementWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(CPP_BlurPanel->IsVisible())
	{
		return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	}
	
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffDetailWidget::GetWidgetName());
	Parameter.bPlayOpenAnimation = false;
	Parameter.bPlayCloseAnimation = false;

	if(const TObjectPtr<UMS_StaffDetailWidget> StaffDetailWidget = Cast<UMS_StaffDetailWidget>(Parameter.InModalWidget))
	{
		StaffDetailWidget->SetDetail(StaffId, WorkDay);
		StaffDetailWidget->ShowButtonPanel(false);
	}
	gWidgetMng.ShowModalWidget(Parameter);
	
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UMS_StaffPropertyElementWidget::OnSelectChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	const int32* StaffIssueType = SelectItems.FindKey(SelectedItem);
	
	if(!StaffIssueType)
	{
		return;
	}

	const EMS_StaffIssueType IssueType = static_cast<EMS_StaffIssueType>(*StaffIssueType);
	// 타입 변경하기.
}

FString UMS_StaffPropertyElementWidget::GetIssueName(int32 _IssueType)
{
	switch(static_cast<EMS_StaffIssueType>(_IssueType))
	{
	case EMS_StaffIssueType::Payment:
		return TEXT("Payment");
	case EMS_StaffIssueType::RemoveItemsFromDisplay:
	case EMS_StaffIssueType::AddItemsToDisplay:
		return TEXT("Store Display");
	case EMS_StaffIssueType::RemoveItemsFromShelf:
		return TEXT("Return Item");
	case EMS_StaffIssueType::AddItemsToShelf:
		return TEXT("Shelf Loading");
	default:
		return TEXT("멍때리기");
	}
}
