// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AssassinsCreedTurkey : ModuleRules
{
	public AssassinsCreedTurkey(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
