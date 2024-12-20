

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ConstructWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConstructWidget : public UMS_Widget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void OnShow();

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_TestBTN1;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_TestBTN2;
};
