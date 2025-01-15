// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SlotWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void SetSlot(int32 aItemId) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Slot = nullptr;
};
