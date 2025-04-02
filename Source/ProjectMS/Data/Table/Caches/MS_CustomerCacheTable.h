// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_Customer.h"
#include "MS_CustomerCacheTable.generated.h"

struct FMS_CustomerData
{
public:
	FMS_CustomerData() {};
	FMS_CustomerData(const FString& aCustomerName, int32 aDuckColor, int32 aCharacterBPPathFile, int32 aMaxItemKind, int32 aMaxItemCount);

	FORCEINLINE int32 GetCharacterBPPathFile() const { return CharacterBPPathFile; }

	// 1000원을 지불했다는 뜻 테스트용 ( 나중에 계산 ) 
	void Paid() { PricePaid = 1000;}
	
	FORCEINLINE bool GetPaid() const { return PricePaid > 0; }

	void GetRemainItems(TMap<int32, int32>& RemainItems);
	void PickUpItem(int32 _PickUpItemTableId, int32 _PickUpItemCount);
	
	void GetAllPickUpItem(TMap<int32, int32>& aPickUpItems) const { aPickUpItems = PickUpItems; }
	void GetWannaItem(TMap<int32, int32>& _WannaItems) const { _WannaItems = WannaBuyItems; }
	bool IsPickUpAllItems();
	bool IsExceptAnyWannaItem();
	bool IsAnyPickUpItemsNotHave() const;
	
	FORCEINLINE FString& GetName() { return CustomerName; }

private:
	FString CustomerName = {};
	int32 DuckColor = 0;
	int32 CharacterBPPathFile = 0;
	TMap<int32, int32> WannaBuyItems = {};
	TMap<int32, int32> PickUpItems = {};
	int32 PricePaid = 0;
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	void MakeNewCustomerData(FMS_CustomerData& NewCustomerData);

private:
	TMap<int32, FMS_Customer*> CustomerDatas = {};
	TArray<FString> CustomerFirstName = {};
	TArray<FString> CustomerLastName = {};
};
