// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Button.h"
#include "MS_MarketPlayButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketPlayButton : public UMS_Button
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString Text;
	
	UPROPERTY(Meta = (BindWidget));
	TObjectPtr<class UTextBlock> CPP_ButtonText = nullptr;
};
