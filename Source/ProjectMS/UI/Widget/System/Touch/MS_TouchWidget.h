

#pragma once

#include "CoreMinimal.h"
#include "Widget/Account/MS_AccountWidget.h"
#include "MS_TouchWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TouchWidget : public UMS_AccountWidget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/System/Touch/TouchWidget.TouchWidget")); }
	
	virtual void NativeConstruct() override;
	
	void RebuildTouchWidget();
	
	void PlayActive();

private:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNiagaraSystemWidget> CPP_TouchEffectWidget = nullptr;
};
