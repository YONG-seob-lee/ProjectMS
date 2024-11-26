#pragma once

#include "CoreMinimal.h"

class UXDebugDialogueHandler
{
public:
	UXDebugDialogueHandler();
	void Activate();
	void Deactivate();
	void RegisterToolBar();
	void UnregisterToolBar();
	void RegisterDebugDialogueDockTab();
	void UnregisterDebugDialogueDockTab();
	void RegisterEditorUtilityWidgetDockTab();
	void UnregisterEditorUtilityWidgetDockTab();
	void OnToolBarButtonClick();
	void OnAssetSelect(const struct FAssetData& aAssetData);
	void MarkTransientFlagRecursive(class UEditorUtilityWidget* aEditorUtilityWidget);

	// Property
public:
	TSharedPtr<class FExtender> ToolBarExtenderPtr = nullptr;
	class SDockTab* EditorUtilityWidgetDockTab = nullptr;
	
	class UEditorUtilityWidgetBlueprint* EditorUtilityWidgetBlueprint = nullptr;
	class UEditorUtilityWidget* EditorUtilityWidget = nullptr;
};