// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_ItemManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMS_OnClickedItem, int32, int32); /* ItemId, ItemType */
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnClickedTileViewItem, int32)

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemManager : public UMS_ManagerBase
{
	GENERATED_BODY()
	
	UMS_ItemManager();
	virtual ~UMS_ItemManager() override;

public:
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime) override;
	
	FORCEINLINE TMap<int32, int32> GetCurrentItems() { return Items; }
	FORCEINLINE TMap<int32, int32> GetShelfItems() { return ShelfItems; }
	FORCEINLINE void SetItems(const TMap<int32, int32>* aTakeItems) { Items = *aTakeItems; }

	void GetStaffProfileElementData(TArray<TObjectPtr<class UMS_StaffProfileElementData>>& aProfileDatas) const;
	
	void SetStaffProperty(int32 aStaffId, class UMS_StaffPropertyElementData* aStaffProperty);
	void GetStaffPropertys(TArray<UMS_StaffPropertyElementData*>& aStaffPropertys);
	
	FMS_OnClickedItem OnClickedItemDelegate;
	
	FMS_OnClickedTileViewItem OnClickedTileViewItem;
private:
	TMap<int32, int32> Items = {};
	TMap<int32, int32> ShelfItems = {};
	TMap<int32, struct FMS_StorageData*> Stand = {};

	// 나중에 서버에서 받을지 미리 캐싱해뒀다 쓸지 고려
	UPROPERTY()
	TArray<TObjectPtr<UMS_StaffProfileElementData>> StaffProfileDatas;

	UPROPERTY()
	TMap<int32, UMS_StaffPropertyElementData*> StaffPropertys;
	
public:
	inline static TObjectPtr<UMS_ItemManager> ItemManager = nullptr;
	static UMS_ItemManager* GetInstance();

	
#define gItemMng (*UMS_ItemManager::GetInstance())
};