// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_ItemElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/SystemWidgets/ListView/ItemElement.ItemElement")); }

	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void InitializeItem(const FString& aItemName, UTexture2D* aItemImage);

	FORCEINLINE UTexture2D* GetItemImage() const { return ItemImage; }
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_ItemImage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_CountText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ItemName = nullptr;

	FString ItemName = FString();
	UPROPERTY()
	UTexture2D* ItemImage = nullptr;
};
