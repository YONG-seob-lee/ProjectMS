// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ExtensionWidget.h"

#include "MS_ExtensionButtonWidget.h"
#include "Widget/System/MS_ContentButtonWidget.h"
#include "Widget/WidgetComponent/MS_VerticalBox.h"

void UMS_ExtensionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 나중에 동적으로 배치할 수있게 개선할 예정
	// TODO 청아 : gCommandMng 를 이용하여 추가 개선 작업
	
	if(CPP_VerticalBox)
	{
		// if(TObjectPtr<UMS_ExtensionButtonWidget> ExtensionButton = Cast<UMS_ExtensionButtonWidget>(CPP_VerticalBox->GetChildAt(0)))
		// {
		// 	ExtensionButton->
		// }
	}
}
