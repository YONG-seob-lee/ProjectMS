// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConfirmButton.h"

#include "Components/TextBlock.h"

void UMS_ConfirmButton::SetButtonName(const FString& aButtonString) const
{
	if(CPP_ButtonName)
	{
		CPP_ButtonName->SetText(FText::FromString(aButtonString));
	}
}
