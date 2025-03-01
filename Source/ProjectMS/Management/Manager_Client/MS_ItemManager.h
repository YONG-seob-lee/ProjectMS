// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
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

	virtual auto BeginPlay() -> void override;
	virtual void Tick(float aDeltaTime) override;

	FMS_OnClickedItem OnClickWidgetConstructItemDelegate;
	FMS_OnClickedTileViewItem OnClickedTileViewItem;
	
	// Items
	void GetRemainItems(TMap<int32, int32>& OutItems) const;
	int32 GetRemainItemCount(int32 aItemId) const;

	void GetStaffItems(TMap<int32, int32>& OutItems) const;
	int32 GetStaffItemCount(int32 aItemId) const;

	void GetCustomerItems(TMap<int32, int32>& OutItems) const;
	int32 GetCustomerItemCount(int32 aItemId) const;

	void GetStorageItems(EMS_ZoneType aZoneType, TMap<int32, int32>& OutItems, EMS_TemperatureType aTemperatureType = EMS_TemperatureType::Undefined) const;
	int32 GetStorageItemCount(EMS_ZoneType aZoneType, int32 aItemId) const;
	
	bool CanDeliveryToStorage(int32 aItemId, int32 aDeliveryCount, EMS_ZoneType aZoneType, TArray<TWeakObjectPtr<class UMS_StorageUnit>>& aOutDeliveryTargetStrage) const;
	bool CanPickUpFromStorage(int32 aItemId, EMS_ZoneType aZoneType, TArray<TWeakObjectPtr<class UMS_StorageUnit>>& aOutPickUpTargetStorages) const;

	void GetNotPlacedItems(TMap<int32, int32>& OutItems);
	int32 GetNotPlacedItemCount(int32 aItemId) const;
	void GetCacheNotPlacedItems(TMap<int32, int32>& OutItems) const;
	int32 GetCacheNotPlacedItemCount(int32 aItemId) const;

	void UpdateNotPlacedItemsToPalletItems();
	void UpdateNotPlacedItemsToPalletItems(TWeakObjectPtr<class UMS_StorageUnit> aStorageUnit);

	FORCEINLINE void UpdateItems(const TMap<int32, int32>& aItems) { Items = aItems; }
	FORCEINLINE void UpdateOrderItems(const TMap<int32, int32>& aOrderItems) { OrderItems = aOrderItems; }
	FORCEINLINE void GetOrderItems(TMap<int32, int32>& aOrderItems) const { aOrderItems = OrderItems; }
	
	bool IsAvailablePurchase() const;
	
	// Furniture
	void GetNotDeployFurniture(TMap<int32, int32>& aNotDeployFurnitures);
	
	FORCEINLINE void UpdateFurnitures(TMap<int32, int32> aFurnitures) { Furnitures = aFurnitures; }
	FORCEINLINE void UpdateOrderFurnitures(TMap<int32, int32> aOrderFurnitures) { OrderFurnitures = aOrderFurnitures; }

	FORCEINLINE void GetAllFurnitureDatas(TMap<FIntVector2, FMS_FurniturePositionData>& aOutFurnitureDatas) const
	{
		aOutFurnitureDatas = GridPositionToMarketFurnitureDatas;
	}
	
	void AddFurnitureData(int32 aFurnitureTableId, const FIntVector2& aGridPosition, EMS_Rotation aRotation);
	void AddFurnitureData(FMS_FurniturePositionData aFurnitureData);
	void RemoveFurnitureData(FIntVector2 aGridPosition);

	void InitializePlayerDatas();
	void SaveFurniturePosition() const;
	
	// Staff
	void GetStaffProfileElementData(TArray<TObjectPtr<class UMS_StaffProfileElementData>>& aProfileDatas) const;
	void UpdateStaffProperty(TArray<FMS_PlayerStaffData>& aStaffDatas);
	void GetStaffProperties(TArray<class UMS_StaffPropertyElementData*>& aStaffProperties);

private:
	// Items
	TMap<int32, int32> Items = {};
	TMap<int32, int32> OrderItems = {};
	TMap<int32, int32> SoldItems = {};
	TMap<int32, int32> CacheNotPlacedItems = {};


	// Furniture
	TMap<int32, int32> Furnitures = {};
	TMap<int32, int32> OrderFurnitures = {};
	TMap<FIntVector2, FMS_FurniturePositionData> GridPositionToMarketFurnitureDatas = {};

	// Staff
	UPROPERTY()
	TArray<TObjectPtr<UMS_StaffProfileElementData>> StaffProfileDatas;

	UPROPERTY()
	TMap<int32, UMS_StaffPropertyElementData*> StaffPropertys;




	
public:
	inline static TObjectPtr<UMS_ItemManager> ItemManager = nullptr;
	static UMS_ItemManager* GetInstance();
	
#define gItemMng (*UMS_ItemManager::GetInstance())
};