// 에픽게임즈의 모든 권리 보유.

using UnrealBuildTool;
using System.Collections.Generic;

public class DEEPSLEEPEditorTarget : TargetRules
{
	public DEEPSLEEPEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		ExtraModuleNames.Add("DEEPSLEEP");
	}
}
