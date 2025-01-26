// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FinancialManagementWidget.h"

#include "Manager_Client/MS_ScheduleManager.h"
#include "Widget/Finance/MS_TotalFinanceWidget.h"
#include "Widget/ListViewElement/MS_MonthFinancialElementWidget.h"
#include "Widget/ListViewElement/ElementData/MS_MonthFinancialElementData.h"
#include "Widget/WidgetComponent/MS_ListView.h"

void UMS_FinancialManagementWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	if(CPP_FinancialIndicator)
	{
		CPP_FinancialIndicator->SetIndicatorString();
	}
	
	if(CPP_MonthFinancialListView)
	{
		TArray<UMS_MonthFinancialElementData*> MonthFinancialElementDatas;
		gScheduleMng.GetFinancialData(MonthFinancialElementDatas);
		CPP_MonthFinancialListView->SetListItems(MonthFinancialElementDatas);
	}

	if(CPP_TotalFinance)
	{
		// for test
		CPP_TotalFinance->SetTotalFinance(0, 13, 5000, 4000, 1.5f);
	}
}
