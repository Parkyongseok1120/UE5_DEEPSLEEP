// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DEEPSLEEP : ModuleRules
{
	public DEEPSLEEP(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.Add(ModuleDirectory);
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AnimGraphRuntime" });
	}
}
