// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Demo1 : ModuleRules
{
	public Demo1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" , "UMG" });
    }
}
