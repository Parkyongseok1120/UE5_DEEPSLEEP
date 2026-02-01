// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DEEPSLEEP : ModuleRules
{
	public DEEPSLEEP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"DEEPSLEEP",
			"DEEPSLEEP/Variant_Platforming",
			"DEEPSLEEP/Variant_Platforming/Animation",
			"DEEPSLEEP/Variant_Combat",
			"DEEPSLEEP/Variant_Combat/AI",
			"DEEPSLEEP/Variant_Combat/Animation",
			"DEEPSLEEP/Variant_Combat/Gameplay",
			"DEEPSLEEP/Variant_Combat/Interfaces",
			"DEEPSLEEP/Variant_Combat/UI",
			"DEEPSLEEP/Variant_SideScrolling",
			"DEEPSLEEP/Variant_SideScrolling/AI",
			"DEEPSLEEP/Variant_SideScrolling/Gameplay",
			"DEEPSLEEP/Variant_SideScrolling/Interfaces",
			"DEEPSLEEP/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
