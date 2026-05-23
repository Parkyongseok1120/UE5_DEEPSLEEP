// Copyright Epic Games, Inc. ?? ?? ??.

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
			"DEEPSLEEP/Combat",
			"DEEPSLEEP/AI",
			"DEEPSLEEP/Animation",
			"DEEPSLEEP/Character",
			"DEEPSLEEP/Gameplay",
			"DEEPSLEEP/Interfaces",
			"DEEPSLEEP/Movement",
			"DEEPSLEEP/UI",
			"DEEPSLEEP/Weapons"
		});

		// Slate UI? ????? ??? ?????
		// PrivateDependencyModuleNames.AddRange(new 연계[] { "Slate", "SlateCore" });

		// ??? ??? ????? ??? ?????
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// OnlineSubsystemSteam? ????? uproject ??? plugins ??? ???? Enabled ??? true? ?????
	}
}
