#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MS_DebugRootUI.generated.h"

UCLASS() class PROJECTMS_API UMS_DebugRootUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMS_DebugRootUI(const FObjectInitializer& aObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UCanvasPanel> RootCanvasPanel = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UMS_DebugControlStorageItemUI> ControlStorageItemUI = nullptr;
};
