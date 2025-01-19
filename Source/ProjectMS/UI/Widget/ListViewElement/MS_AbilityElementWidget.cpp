// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AbilityElementWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_AbilityElementData.h"

void UMS_AbilityElementWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LevelArray.Emplace(CPP_Level01);
	LevelArray.Emplace(CPP_Level02);
	LevelArray.Emplace(CPP_Level03);
	LevelArray.Emplace(CPP_Level04);
	LevelArray.Emplace(CPP_Level05);
	LevelArray.Emplace(CPP_Level06);
	LevelArray.Emplace(CPP_Level07);
	LevelArray.Emplace(CPP_Level08);
	LevelArray.Emplace(CPP_Level09);
	LevelArray.Emplace(CPP_Level10);
}

void UMS_AbilityElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_AbilityElementData> AbilityElementData = Cast<UMS_AbilityElementData>(aListItemObject))
	{
		CPP_AbilityName->SetText(FText::FromString(AbilityElementData->GetAbilityName()));

		SetLevel(AbilityElementData->GetAbilityLevel());
	}
}

void UMS_AbilityElementWidget::SetLevel(int32 aLevel)
{
	for(int32 i = 0 ; i < LevelArray.Num(); i++)
	{
		if(i < aLevel)
		{
			LevelArray[i]->SetColorAndOpacity(FLinearColor::Black);
		}
		else
		{
			LevelArray[i]->SetColorAndOpacity(FLinearColor::Gray);
		}
	}
}
