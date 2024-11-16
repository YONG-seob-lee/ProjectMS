// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectMS : ModuleRules
{
	public ProjectMS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
			, "Slate", "SlateCore", "GameplayCameras", "AIModule", "NavigationSystem"
			, "ProceduralMeshComponent", "AssetRegistry", "UMG"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CommonInput", "CommonUI", "EnhancedInput"
		});

		PublicIncludePaths.AddRange(new string[] { "ProjectMS" });
		PrivateIncludePaths.AddRange(new string[] { "ProjectMS" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
