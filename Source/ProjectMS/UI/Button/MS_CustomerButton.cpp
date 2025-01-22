// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerButton.h"

#include "Components/Image.h"

void UMS_CustomerButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if(Texture)
	{
		if(CPP_ButtonImage)
		{
			CPP_ButtonImage->SetBrushFromTexture(Texture);
		}
	}
}

void UMS_CustomerButton::SetActive(bool bActive) const
{
	CPP_ActiveImage->SetVisibility(bActive ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}
