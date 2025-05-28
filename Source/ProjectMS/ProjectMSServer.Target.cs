using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectMSServerTarget : TargetRules
{
	public ProjectMSServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ProjectMS");
	}
};
