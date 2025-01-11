

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TouchWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TouchWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/SystemWidgets/Touch/TouchWidget.TouchWidget")); }

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void RebuildTouchWidget() const;
	void ReleasedNiagaraActor() const;
	
	void PlayActive() const;

private:
	float ElapsedTime = 0.f;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UNiagaraSystemWidget> CPP_TouchEffectWidget = nullptr;
};
