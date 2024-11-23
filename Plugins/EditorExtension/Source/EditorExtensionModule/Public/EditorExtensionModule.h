#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class EditorExtensionModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    void InitializeSlateStyleSet();
    void FinalizeSlateStyleSet();

    // Property
public:
    TSharedPtr<FSlateStyleSet> EditorExtensionModuleSlateStyleSetPtr = nullptr;
    class UXCurrentLevelSwitchHandler* CurrentLevelSwitchHandler = nullptr;
    class UXDebugDialogueHandler* DebugDialogueHandler = nullptr;
};