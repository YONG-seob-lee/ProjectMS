// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_CountWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CountWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void SetCount(int32 aMolecular, int32 aDenominator) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_CountText = nullptr;
};
