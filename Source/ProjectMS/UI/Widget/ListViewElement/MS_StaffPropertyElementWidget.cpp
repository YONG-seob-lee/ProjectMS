// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffPropertyElementWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/ComboBoxString.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Controller/MS_PlayerController.h"
#include "ElementData/MS_StaffPropertyElementData.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "PlayerState/MS_PlayerState.h"
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
	StaffIdTag = StaffPropertyData->GetStaffIdTag();
	StaffUIPriorityType = StaffPropertyData->GetStaffUIPriorityType();
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
		int32 SelectedIndex = INDEX_NONE;
		
		for(int32 i = 0 ; i < static_cast<int32>(EMS_StaffUIPriorityType::EMS_StaffUIPriorityType_Max); ++i)
		{
			const FString IssueName = GetUIIssueName(i);
			CPP_StaffIssueBox->AddOption(IssueName);
			SelectItems.Emplace(i, IssueName);

			if (i == static_cast<int32>(StaffUIPriorityType))
			{
				SelectedIndex = i;
			}
		}

		CPP_StaffIssueBox->SetSelectedIndex(SelectedIndex);
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
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}
	
	const int32* pUIPriorityType = SelectItems.FindKey(SelectedItem);
	if(!pUIPriorityType)
	{
		return;
	}
	StaffUIPriorityType = static_cast<EMS_StaffUIPriorityType>(*pUIPriorityType);
	
	TArray<EMS_StaffIssueType> PriorityOfWorks;
	
	switch (StaffUIPriorityType)
	{
	case EMS_StaffUIPriorityType::PaymentFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}

	case EMS_StaffUIPriorityType::DisplayFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}
		
	case EMS_StaffUIPriorityType::ShelfFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf,
				EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay};
			break;
		}

	case EMS_StaffUIPriorityType::PaymentOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment};
			break;
		}

	case EMS_StaffUIPriorityType::DisplayOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay};
			break;
		}

	case EMS_StaffUIPriorityType::ShelfOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}

	default:
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}
	}
	
	// Write To Player Data
	PlayerState->RegisterStaffPriorityOfWorks(StaffId, StaffIdTag, PriorityOfWorks, StaffUIPriorityType);
	PlayerState->SavePlayerData();
}

FString UMS_StaffPropertyElementWidget::GetUIIssueName(int32 aUIIssueType)
{
	switch(static_cast<EMS_StaffUIPriorityType>(aUIIssueType))
	{
	case EMS_StaffUIPriorityType::PaymentFirst:
		return TEXT("Payment First");
	case EMS_StaffUIPriorityType::DisplayFirst:
		return TEXT("Display First");
	case EMS_StaffUIPriorityType::ShelfFirst:
		return TEXT("Shelf First");
	case EMS_StaffUIPriorityType::PaymentOnly:
		return TEXT("Payment Only");
	case EMS_StaffUIPriorityType::DisplayOnly:
		return TEXT("Display Only");
	case EMS_StaffUIPriorityType::ShelfOnly:
		return TEXT("Shelf Only");
	default:
		return TEXT("멍때리기");
	}
}
