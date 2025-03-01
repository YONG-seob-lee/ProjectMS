// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class ProjectMS : ModuleRules
{
	public ProjectMS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
			, "Slate", "SlateCore", "GameplayCameras", "AIModule", "NavigationSystem", "GamePlayTasks"
			, "ProceduralMeshComponent", "AssetRegistry", "UMG", "CommonInput", "NiagaraUIRenderer"
			, "LevelSequence", "MovieScene"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CommonInput", "CommonUI", "EnhancedInput"
		});

		PublicIncludePaths.AddRange(new string[] { "ProjectMS", "ProjectMS/Actor", "ProjectMS/CoreClass",
			"ProjectMS/Data", "ProjectMS/Level", "ProjectMS/Management", "ProjectMS/UI", "ProjectMS/Unit", 
			"ProjectMS/Utility" });
		PrivateIncludePaths.AddRange(new string[] { "ProjectMS" });

		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			var manifestFile = Path.Combine(ModuleDirectory, "AndroidSanitizePermissions_UPL.xml");
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", manifestFile);
		}
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
