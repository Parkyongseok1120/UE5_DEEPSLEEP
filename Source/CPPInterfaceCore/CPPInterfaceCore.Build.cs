// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CPPInterfaceCore : ModuleRules
{
    public CPPInterfaceCore(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.CPlusPlus;

        // PCH(Precompiled Header) 설정: 빠른 컴파일을 위해 명시적 또는 공유 PCH 사용
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // [중요 수정] CoreUObject는 Shipping 빌드에서도 링크 문제를 방지하기 위해 기본 포함하는 것이 안전합니다.
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject"
        });

        // 개발(Editor/Development) 환경에서만 필요한 모듈 설정
        if (Target.Configuration != UnrealTargetConfiguration.Shipping)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "AutomationController",
            });
        }

        // C++ 예외 처리 허용 (std::try, catch 사용 시 필요)
        bEnableExceptions = true;

        // C++ 20 표준 사용
        CppStandard = CppStandardVersion.Cpp20;

        // Include 경로 설정
        PublicIncludePaths.Add(ModuleDirectory + "/Public");
        PrivateIncludePaths.Add(ModuleDirectory + "/Private");
    }
}