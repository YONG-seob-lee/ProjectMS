// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ExtensionWidget.h"

#include "MS_ExtensionButtonWidget.h"
#include "MS_WidgetManager.h"
#include "Components/CanvasPanel.h"
#include "Components/VerticalBoxSlot.h"
#include "Widget/WidgetComponent/MS_VerticalBox.h"

void UMS_ExtensionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 나중에 동적으로 배치할 수있게 개선할 예정
	// TODO 청아 : gCommandMng 를 이용하여 추가 개선 작업
	
	if(!CPP_VerticalBox)
	{
		return;
	}

	CPP_VerticalBox->ClearChildren();

	for(int32 i = 0 ; i <= static_cast<int32>(EMS_ModeType::CustomerManagement); i++)
	{
		if(const TObjectPtr<UMS_ExtensionButtonWidget> ExtensionButton = Cast<UMS_ExtensionButtonWidget>(gWidgetMng.Create_Widget_NotManaging(UMS_ExtensionButtonWidget::GetWidgetPath())))
		{
			ExtensionButton->SetModeType(static_cast<EMS_ModeType>(i));
			CPP_VerticalBox->AddChild(ExtensionButton);
			if(const TObjectPtr<UVerticalBoxSlot> VSlot = Cast<UVerticalBoxSlot>(ExtensionButton->Slot))
			{
				FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Fill);
				Size.Value = 1.f;
				VSlot->SetSize(Size);
			}
			
			if(TObjectPtr<UCanvasPanel> Panel = NewObject<UCanvasPanel>())
			{
				CPP_VerticalBox->AddChild(Panel);
				if(const TObjectPtr<UVerticalBoxSlot> VSlot = Cast<UVerticalBoxSlot>(ExtensionButton->Slot))
				{
					FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Fill);
					Size.Value = 0.2f;
					VSlot->SetSize(Size);
				}	
			}
		}
	}
}
