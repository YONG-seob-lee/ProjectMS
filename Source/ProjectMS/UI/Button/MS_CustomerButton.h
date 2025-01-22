// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Button.h"
#include "MS_CustomerButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerButton : public UMS_Button
{
	GENERATED_BODY()
public:
	virtual void SynchronizeProperties() override;

	void SetActive(bool bActive) const;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTexture2D> Texture = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_ButtonImage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_ActiveImage = nullptr;
};
