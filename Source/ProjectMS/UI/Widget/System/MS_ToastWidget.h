

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ToastWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ToastWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	virtual void OnAnimFinished(const FName& aAnimName) override;

	void SetToastMsg(const FString& aMessage) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ToastText = nullptr;
};
