// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ContentsPartWidget.h"

#include "MS_ContentButtonWidget.h"
#include "MS_Define.h"
#include "MS_SceneManager.h"
#include "MS_TableManager.h"
#include "Widget/WidgetComponent/MS_HorizontalBox.h"

void UMS_ContentsPartWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(const TObjectPtr<UMS_ContentButtonWidget> ContentButtonWidget = Cast<UMS_ContentButtonWidget>(CPP_HorizontalBox->GetChildAt(0)))
	{
		const FString ImagePath = gTableMng.GetPath(EMS_TableDataType::BasePathImgFile, 1);
		if(UTexture2D* IconImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *ImagePath)))
		{
			ContentButtonWidget->SetIconImage(IconImage);
		}

		ContentButtonWidget->GetOnClickedDelegate().AddUObject(this, &UMS_ContentsPartWidget::OnClickMarketButton);
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
