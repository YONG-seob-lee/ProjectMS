// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "Table/RowBase/MS_Item.h"
#include "Table/RowBase/MS_StorageData.h"
#include "MS_InventoryManager.generated.h"

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
	Fruit,
	Fish,
	Beverage,
	Frozen,
	Snack,
	FrozenSnack
};

UENUM()
enum class EMS_StorageType : uint8
{
	Undefined = 0,
	Fresh,
	Refrigeration,
	Freezing
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_InventoryManager : public UMS_ManagerBase
{
	GENERATED_BODY()
	
	UMS_InventoryManager();
	virtual ~UMS_InventoryManager() override;

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
private:
	TMap<int32, FMS_Item*> Items = {};
	TMap<int32, FMS_StorageData*> Stand = {};
	
public:
	inline static TObjectPtr<UMS_InventoryManager> InventoryManager = nullptr;
	static UMS_InventoryManager* GetInstance();
	
#define gInvenMng (*UMS_InventoryManager::GetInstance())
};
