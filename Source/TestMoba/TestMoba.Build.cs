// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestMoba : ModuleRules
{
	public TestMoba(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "CableComponent" });
    }
}
