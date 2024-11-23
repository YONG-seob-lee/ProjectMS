#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "XSubEditorUtilityWidget.generated.h"

UCLASS(Abstract) class UXSubEditorUtilityWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXSubEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UCanvasPanel* RootCanvasPanel = nullptr;
};