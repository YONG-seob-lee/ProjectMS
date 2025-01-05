// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "Table/RowBase/MS_Item.h"
#include "Table/RowBase/MS_StorageData.h"
#include "MS_ItemManager.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMS_OnClickedItem, int32, int32); /* ItemId, ItemType */
DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnClickedTileViewItem, int32)

// 임시
struct FPacketItemDatas
{
public:
	int32 ItemId = 0;
	FVector Vector;
	FRotator Rotator;
};

UENUM()
enum class EMS_ItemType : uint8
{
	Undefined = 0,
	Money,
	Cash,
	Fruit,
	Fish,
	Beverage,
	Frozen,
	Snack,
	FrozenSnack,
	Storage
};

UENUM()
enum class EMS_StorageType : uint8
{
	Undefined = 0,
	Pallet,
	Shelf,
	Display
};

UENUM()
enum class EMS_TemperatureType : uint8
{
	Undefined = 0,
	Constant,
	Refrigeration,
	Freezing
};
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

	void CreateItem(int32 aItemId);
	void CreateItem(const TMap<int32, FPacketItemDatas*>& aItems);

	FMS_OnClickedItem OnClickedItemDelegate;
	
	FMS_OnClickedTileViewItem OnClickedTileViewItem;
private:
	TMap<int32, FMS_Item*> Items = {};
	TMap<int32, FMS_StorageData*> Stand = {};
	
public:
	inline static TObjectPtr<UMS_ItemManager> InventoryManager = nullptr;
	static UMS_ItemManager* GetInstance();

	
#define gItemMng (*UMS_ItemManager::GetInstance())
};
