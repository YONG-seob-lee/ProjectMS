#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "XEditorUtilityWidget.generated.h"

UCLASS() class UXEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UCanvasPanel* RootCanvasPanel = nullptr;
};