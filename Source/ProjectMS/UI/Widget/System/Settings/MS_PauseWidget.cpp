// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PauseWidget.h"

#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_PauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_BlurButton)
	{
		CPP_BlurButton->GetOnClickedDelegate().AddUObject(this, &UMS_PauseWidget::OnClickedBlurButton);
	}

	PauseHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateWeakLambda(this, [this](float DeltaTime)
	{
		this->PauseTextAnimationTimer(DeltaTime);
		return true;
	}), 0.5f);
	
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UMS_PauseWidget::OnClickedBlurButton()
{
	gWidgetMng.CloseModalWidget([this]()
	{
		FTSTicker::GetCoreTicker().RemoveTicker(PauseHandle);
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	});
}

void UMS_PauseWidget::PauseTextAnimationTimer(float DeltaTime)
{
	DotCount++;
	FString PauseText = TEXT("Pause");
	for(int32 i = 0 ; i < DotCount ; i++)
	{
		PauseText += TEXT(".");
	}
	
	CPP_PauseText->SetText(FText::FromString(PauseText));
	if(DotCount >= Dot::MaxCount)
	{
		DotCount = 0;
	}
}
