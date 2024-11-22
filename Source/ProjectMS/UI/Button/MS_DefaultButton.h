// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Button.h"
#include "MS_DefaultButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_DefaultButton : public UMS_Button
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

private:
	void OnClickDefaultButton();
};
