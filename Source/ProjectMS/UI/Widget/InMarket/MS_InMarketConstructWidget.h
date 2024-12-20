

#pragma once

#include "CoreMinimal.h"
#include "MS_InMarketModeWidget.h"
#include "MS_InMarketConstructWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_InMarketConstructWidget : public UMS_InMarketModeWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	void OnShow() override;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ConstructWidget> CPP_ConstructWidget;
};
