using System.IO;
using UnrealBuildTool;
using System.Collections.Generic;

public class EditorExtensionModule : ModuleRules
{
    public EditorExtensionModule(ReadOnlyTargetRules Target) : base(Target)
    {
        bUsePrecompiled = true;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp17;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EngineSettings", "ApplicationCore", "Projects", "HotReload", "Json", "JsonUtilities" });
        if (Target.bBuildEditor == true)
            PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EditorStyle", "ContentBrowser", "AssetRegistry", "UnrealEd", "LevelEditor", "Blutility", "UMG", "UMGEditor", "ScriptableEditorWidgets", "GraphEditor" });

        string PublicSourceFolderPath = Path.Combine(ModuleDirectory, "Public");
        string PrivateSourceFolderPath = Path.Combine(ModuleDirectory, "Private");
        string[] LineArray = File.ReadAllLines(Path.Combine(PublicSourceFolderPath, "Utility/DebugMacro.h"));
        for (int i = 0; i < LineArray.Length; i++)
        {
            if (i != 0 && i != LineArray.Length - 1)
                PublicDefinitions.Add(LineArray[i]);
        }
    
        string ThirdPartyFolderPath = Path.Combine(ModuleDirectory, "../ThirdParty");
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
#if DEBUG
            PublicAdditionalLibraries.AddRange(new string[] { Path.Combine(ThirdPartyFolderPath, "OpenXLSX/lib/debug/OpenXLSXd.lib") });
#else
            PublicAdditionalLibraries.AddRange(new string[] { Path.Combine(ThirdPartyFolderPath, "OpenXLSX/lib/release/OpenXLSX.lib") });
#endif
            PublicIncludePaths.AddRange(new string[] { Path.Combine(ThirdPartyFolderPath, "OpenXLSX/include") });
            PrivateIncludePaths.AddRange(new string[] { Path.Combine(ThirdPartyFolderPath, "OpenXLSX/include") });
        }
    }
}