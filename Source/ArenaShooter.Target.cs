// Arena Shooter

using UnrealBuildTool;
using System.Collections.Generic;

public class ArenaShooterTarget : TargetRules
{
	public ArenaShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ArenaShooter" } );
	}
}
