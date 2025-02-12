// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ShelfStatus.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ShelfStatus : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	FORCEINLINE void SetOnClickedShelfSlotFunc(const TFunction<void(int32, int32)>& aFunc) { OnClickedShelfSlotCallback = aFunc; }
	FORCEINLINE void SetDisplaySlotIndex(int32 aDisplaySlotIndex) { DisplaySlotIndex = aDisplaySlotIndex; }
	void SetTileView();

private:
	void OnClickedShelfSlotButton(int32 aItemId);

	int32 DisplaySlotIndex = INDEX_NONE;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_TileView = nullptr;

	TFunction<void(int32, int32)> OnClickedShelfSlotCallback = nullptr;
};
