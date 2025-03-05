// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_AIUnit.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Component/Actor/MS_AIParameterComponent.h"
#include "Widget/Dialog/SpeechBubble/MS_SpeechBubbleWidget.h"
#include "MS_MarketAIUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketAIUnit : public UMS_AIUnit
{
	GENERATED_BODY()

public:
	virtual bool CreateUnitActor(const FVector& aPosition, const FRotator& aRotator) override;
	virtual bool SetUnitCharacter(TObjectPtr<class AMS_CharacterBase> aUnitCharacter, bool bForced = false);
	
	FIntVector2 GetActorGridPosition() const;
	FVector GetActorLocation() const;
	
	const TArray<FIntVector2>& GetTargetPositions() const { return CacheTargetPositions; }
	void SetTargetPositions(const TArray<FIntVector2>& aTargetPositions) { CacheTargetPositions = aTargetPositions; }

	const TArray<FIntVector2>& GetPath() const { return CachePath; }
	void SetPath(const TArray<FIntVector2>& aCachePath) { CachePath = aCachePath; }

	void ResetPath();

	// Location
	bool IsGridSizeXOdd() const { return false; }
	bool IsGridSizeYOdd() const { return false; }
	
	EBTNodeResult::Type UpdateActorLocationByPath();
	void OnReachPathLocation(const FVector2D& aReachedLocation);

	// Slot
	FORCEINLINE void GetSlotDatas(TArray<FMS_SlotData>& aOutSlotDatas) const { aOutSlotDatas = SlotDatas; }
	FMS_SlotData GetSlotData(int32 aSlotId) const;

	FORCEINLINE virtual int32 GetSlotCount() const { return 0; }

	void ResetSlotDatas();
	bool AddCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount);
	bool SubtractCurrentItemCount(int32 aSlotId, int32 aItemId, int32 aCount);

	
	// Process Shopping
	void ShowChatting(EMS_ChattingType ChattingType = EMS_ChattingType::Undefined) const;
	void ShowImage(EMS_SpeechImageType SpeechImageType) const;
	bool IsChatBefore() const;
	void ResetChatting() const;
	
protected:
	virtual void OnChangeCurrentSlotDatas(bool bUpdateNotPlacedItems = false);

	
private:
	// Location
	TArray<FIntVector2> CacheTargetPositions = {};	// Blackboard에 Array형을 지원 안함
	TArray<FIntVector2> CachePath = {};

	EMS_Direction CacheDirection = EMS_Direction::None; 
	EMS_Direction CacheNextDirection = EMS_Direction::None;

protected:
	// Slot
	UPROPERTY()
	TArray<FMS_SlotData> SlotDatas;
};
