

#pragma once

#include "CoreMinimal.h"
#include "MS_InMarketModeWidget.h"
#include "MS_InMarketNormalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_InMarketNormalWidget : public UMS_InMarketModeWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void OnClickConstructButton();
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ConstructButton;
};
