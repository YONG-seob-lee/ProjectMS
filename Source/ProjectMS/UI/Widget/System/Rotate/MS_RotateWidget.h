

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_RootWidget.h"
#include "Widget/MS_Widget.h"
#include "MS_RotateWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_RotateWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	void OnClockedLeftRotateButton();
	void OnClickedRightRotateButton();
	void OnClickedReturnRotateButton();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_RotateButtonLeft = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_RotateButtonRight = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ReturnRotateButton = nullptr;
};
