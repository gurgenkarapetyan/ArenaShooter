// Arena Shooter

using UnrealBuildTool;
using System.Collections.Generic;

public class ArenaShooterEditorTarget : TargetRules
{
	public ArenaShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ArenaShooter" } );
	}
}
