// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DEEPSLEEP : ModuleRules
{
    public DEEPSLEEP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // [참고] ModuleDirectory를 PublicIncludePaths에 직접 추가하는 것은 보통 불필요하나, 구조에 따라 남겨둡니다.
        PublicIncludePaths.Add(ModuleDirectory);

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AnimGraphRuntime",
            "AIModule",
            "GameplayTags",
            "UMG",
            "CPPInterfaceCore" // 커스텀 모듈 의존성
        });

        // [수정] CPPInterfaceCore의 Public 경로를 수동으로 넣을 필요가 없습니다. 
        // 위에서 PublicDependencyModuleNames에 "CPPInterfaceCore"를 추가했으므로 자동 연결됩니다.

        // 개발 및 테스트 빌드에서만 필요한 모듈
        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "AutomationController",
                "FunctionalTesting",
            });
        }

        // 로깅 관련 모듈
        PrivateDependencyModuleNames.Add("TraceLog");
    }
}