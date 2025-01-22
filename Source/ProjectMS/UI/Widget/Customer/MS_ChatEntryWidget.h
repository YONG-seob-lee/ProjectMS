// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScriptActorComponent/MS_UnitChattingCollectComponent.h"
#include "Widget/MS_Widget.h"
#include "MS_ChatEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ChatEntryWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void SetChatting(TArray<FMS_ChattingParameter>& aChattingParameters) const;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_ChatListView = nullptr; 
};
