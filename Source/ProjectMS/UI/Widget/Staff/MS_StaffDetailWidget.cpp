// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffDetailWidget.h"

#include "Button/MS_Button.h"
#include "Test/TestServer/MS_TestServer.h"
#include "Components/CanvasPanel.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_StaffAbilityCacheTable.h"
#include "Widget/ListViewElement/MS_StaffProfileElementWidget.h"
#include "Widget/ListViewElement/ElementData/MS_AbilityElementData.h"
#include "Widget/WidgetComponent/MS_ListView.h"

void UMS_StaffDetailWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_HireButton->GetOnClickedDelegate().AddUObject(this, &UMS_StaffDetailWidget::OnClickedHireButton);
	CPP_ReconsiderButton->GetOnClickedDelegate().AddUObject(this, &UMS_StaffDetailWidget::OnClickedReconsiderButton);
}

void UMS_StaffDetailWidget::NativeDestruct()
{
	Super::NativeDestruct();

	for(const auto& AbilityElementData : AbilityElementDatas)
	{
		MS_DeleteObject(AbilityElementData);
	}
}

void UMS_StaffDetailWidget::SetDetail(int32 aStaffId)
{
	StaffId = aStaffId;
	
	CPP_ProfileWidget->SetProfile(aStaffId);
	
	const TObjectPtr<UMS_StaffAbilityCacheTable> StaffAbilityTable = Cast<UMS_StaffAbilityCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::StaffAbility));
	MS_ENSURE(StaffAbilityTable);

	if(const FMS_StaffAbility* StaffAbilityData = StaffAbilityTable->GetStaffAbilityData(aStaffId))
	{
		for(int32 i = 1 ; i <= 5 ; i++)
		{
			UMS_AbilityElementData* AbilityElementData = MS_NewObject<UMS_AbilityElementData>();
			AbilityElementData->SetAbilityName(GetAbilityName(i));
			const EMS_AbilityType AbilityType = static_cast<EMS_AbilityType>(i);
			if(AbilityType == EMS_AbilityType::Work)
			{
				AbilityElementData->SetAbilityLevel(StaffAbilityData->Diligence);
			}
			else if(AbilityType == EMS_AbilityType::Endurance)
			{
				AbilityElementData->SetAbilityLevel(StaffAbilityData->Endurance);
			}
			else if(AbilityType == EMS_AbilityType::Diligence)
			{
				AbilityElementData->SetAbilityLevel(StaffAbilityData->Diligence);
			}
			else if(AbilityType == EMS_AbilityType::Kindness)
			{
				AbilityElementData->SetAbilityLevel(StaffAbilityData->Kindness);
			}
			else if(AbilityType == EMS_AbilityType::Plannedness)
			{
				AbilityElementData->SetAbilityLevel(StaffAbilityData->Plannedness);
			}
			AbilityElementDatas.Emplace(AbilityElementData);
		}
		CPP_AbilityListView->SetListItems(AbilityElementDatas);
	}
}

void UMS_StaffDetailWidget::ShowButtonPanel(bool bShow) const
{
	if(CPP_ButtonPanel)
	{
		CPP_ButtonPanel->SetVisibility(bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UMS_StaffDetailWidget::OnClickedHireButton()
{
	gTestServer.RenewStaff(StaffId);
	gWidgetMng.CloseModalWidget();
	gWidgetMng.ShowToastMessage(TEXT("새로운 스텝을 고용하였습니다!!"));
}

void UMS_StaffDetailWidget::OnClickedReconsiderButton()
{
	gWidgetMng.CloseModalWidget();
}

FString UMS_StaffDetailWidget::GetAbilityName(int32 aAbilityType)
{
	switch(static_cast<EMS_AbilityType>(aAbilityType))
	{
	case EMS_AbilityType::Work:
		return TEXT("일머리");
	case EMS_AbilityType::Endurance:
		return TEXT("인내력");
	case EMS_AbilityType::Diligence:
		return TEXT("성실성");
	case EMS_AbilityType::Kindness:
		return TEXT("친절함");
	case EMS_AbilityType::Plannedness:
		return TEXT("계획성");
	default:
		return TEXT("None");
	}
}
