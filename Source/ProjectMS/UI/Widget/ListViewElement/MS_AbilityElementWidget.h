// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_AbilityElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AbilityElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;

	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	
private:
	void SetLevel(int32 aLevel);
	
	TArray<TObjectPtr<class UImage>> LevelArray = {};
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_AbilityName = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level01 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level02 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level03 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level04 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level05 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level06 = nullptr;
	
	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level07 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level08 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level09 = nullptr;

	UPROPERTY(Meta= (BindWidget))
	TObjectPtr<class UImage> CPP_Level10 = nullptr;

	
};
