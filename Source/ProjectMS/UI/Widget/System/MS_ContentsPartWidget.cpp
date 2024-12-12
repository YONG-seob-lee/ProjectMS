// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ContentsPartWidget.h"

#include "MS_ContentButtonWidget.h"
#include "MS_Define.h"
#include "MS_SceneManager.h"
#include "MS_TableManager.h"
#include "MS_WidgetManager.h"
#include "Widget/WidgetComponent/MS_HorizontalBox.h"

void UMS_ContentsPartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 나중에 동적으로 배치할 수있게 개선할 예정
	if(const TObjectPtr<UMS_ContentButtonWidget> ContentButtonWidget = Cast<UMS_ContentButtonWidget>(CPP_HorizontalBox->GetChildAt(0)))
	{
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, 1);
		if(UTexture2D* IconImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			ContentButtonWidget->SetIconImage(IconImage);
		}

		ContentButtonWidget->GetOnClickedDelegate().AddUObject(this, &UMS_ContentsPartWidget::OnClickMarketButton);
	}

	if(const TObjectPtr<UMS_ContentButtonWidget> CommandModeButton = Cast<UMS_ContentButtonWidget>(CPP_HorizontalBox->GetChildAt(2)))
	{
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, 2);
		if(UTexture2D* IconImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			CommandModeButton->SetIconImage(IconImage);
		}
		CommandModeButton->GetOnClickedDelegate().AddUObject(this, &UMS_ContentsPartWidget::OnClickHamburgerButton, CommandModeButton);
	}

	if(const TObjectPtr<UMS_ContentButtonWidget> ModalButton = Cast<UMS_ContentButtonWidget>(CPP_HorizontalBox->GetChildAt(4)))
	{
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, 3);
		if(UTexture2D* IconImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			ModalButton->SetIconImage(IconImage);
		}
		ModalButton->GetOnClickedDelegate().AddUObject(this, &UMS_ContentsPartWidget::OnClickModalButton);
	}

	if(const TObjectPtr<UMS_ContentButtonWidget> ContentButtonWidget = Cast<UMS_ContentButtonWidget>(CPP_HorizontalBox->GetChildAt(6)))
	{
		ContentButtonWidget->GetOnClickedDelegate().AddWeakLambda(this, [this]()
			{
				gWidgetMng.ShowToastMessage(TEXT(""));
			});
	}

	if(const TObjectPtr<UMS_ContentButtonWidget> ContentButtonWidget = Cast<UMS_ContentButtonWidget>(CPP_HorizontalBox->GetChildAt(8)))
	{
		ContentButtonWidget->GetOnClickedDelegate().AddWeakLambda(this, [this]()
			{
				gWidgetMng.ShowToastMessage(TEXT(""));
			});
	}
}

void UMS_ContentsPartWidget::OnClickMarketButton()
{
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::InMarketLevel);
	Command->SetPreviousLevelType(EMS_LevelType::TownLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	gSceneMng.RequestChangeScene(Command);
}

void UMS_ContentsPartWidget::OnClickHamburgerButton(TObjectPtr<UMS_ContentButtonWidget> aCommandModeButton)
{
	if(aCommandModeButton)
	{
		aCommandModeButton->OpenExtensionUI();
	}
}

void UMS_ContentsPartWidget::OnClickModalButton()
{
	gWidgetMng.ShowModalWidget(nullptr);
}
