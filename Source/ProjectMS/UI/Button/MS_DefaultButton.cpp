// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DefaultButton.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "MS_WidgetManager.h"

void UMS_DefaultButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetOnClickedDelegate().AddUObject(this, &UMS_DefaultButton::OnClickDefaultButton);
}

void UMS_DefaultButton::OnClickDefaultButton()
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);
	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	const TObjectPtr<UMS_WidgetManager> WidgetManager = PlayerController->GetWidgetManager();
	MS_CHECK(WidgetManager);

	WidgetManager->ShowToastMessage(TEXT(""));
}
