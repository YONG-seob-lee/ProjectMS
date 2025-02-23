// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LoadingTutorialWidget.h"

#include "MS_Define.h"
#include "Components/TextBlock.h"
#include "Manager_Both/MS_TableManager.h"

void UMS_LoadingTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FillDefaultAnimations();

	SetTutorial();
	PlayAnimationByName(TutorialAnimation::Play);
}

void UMS_LoadingTutorialWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == TutorialAnimation::Play)
	{
		StopAllAnimations();
		SetTutorial();
		PlayAnimationByName(TutorialAnimation::Play);
	}
}

void UMS_LoadingTutorialWidget::SetTutorial()
{
	CPP_TutorialText->SetText(FText::FromStringTable(MS_LocalizedTableId::StringTable, GetRandomTutorial()));
}

FString UMS_LoadingTutorialWidget::GetRandomTutorial()
{
	const EMS_LoadingTutorial TutorialIndex = static_cast<EMS_LoadingTutorial>(FMath::RandRange(static_cast<int32>(EMS_LoadingTutorial::Loading_Tutorial_First), static_cast<int32>(EMS_LoadingTutorial::Loading_Tutorial_Last) - 1));

	return ConvertEnumToString<EMS_LoadingTutorial>("EMS_LoadingTutorial", TutorialIndex);
}
