// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_Tutorial.h"
#include "MS_TutorialCacheTable.generated.h"

UENUM()
enum class EMS_TutorialType
{
	Schedule = 1,
	Market,
	Manage,
	BuyItem,
	BuyFurniture,
	HireStaff,
	ManageStaff,
	ManageCustomer,
	SalesDetail,
	ConstructMode,
};

namespace TutorialLocalizedString
{
	const FString ScheduleDesc = TEXT("Tutorial_Schedule_Desc");
	const FString ScheduleSubDesc = TEXT("Tutorial_Schedule_SubDesc");
	const FString MarketDesc = TEXT("Tutorial_Market_Desc");
	const FString MarketSubDesc = TEXT("Tutorial_Market_SubDesc");
	const FString ManageDesc = TEXT("Tutorial_Manage_Desc");
	const FString ManageSubDesc = TEXT("Tutorial_Manage_SubDesc");
	const FString BuyItemDesc = TEXT("Tutorial_BuyItem_Desc");
	const FString BuyItemSubDesc = TEXT("Tutorial_BuyItem_SubDesc");
	const FString BuyFurnitureDesc = TEXT("Tutorial_BuyFurniture_Desc");
	const FString BuyFurnitureSubDesc = TEXT("Tutorial_BuyFurniture_SubDesc");
	const FString HireStaffDesc = TEXT("Tutorial_HireStaff_Desc");
	const FString HireStaffSubDesc = TEXT("Tutorial_HireStaff_SubDesc");
	const FString ManageStaffDesc = TEXT("Tutorial_ManageStaff_Desc");
	const FString ManageStaffSubDesc = TEXT("Tutorial_ManageStaff_SubDesc");
	const FString ManageCustomerDesc = TEXT("Tutorial_ManageCustomer_Desc");
	const FString ManageCustomerSubDesc = TEXT("Tutorial_ManageCustomer_SubDesc");
	const FString SalesDetailDesc = TEXT("Tutorial_SamesDetail_Desc");
	const FString SalesDetailSubDesc = TEXT("Tutorial_SamesDetail_SubDesc");
	const FString ConstructModeDesc = TEXT("Tutorial_ConstructMode_Desc");
	const FString ConstructModeSubDesc = TEXT("Tutorial_ConstructMode_SubDesc");
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TutorialCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	
	void GetTutorialDesc(int32 TutorialKey, FText& Desc, FText& SubDesc);

private:
	TMap<int32, FMS_Tutorial*> TutorialDatas;
};
