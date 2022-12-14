// Arena Shooter

using UnrealBuildTool;

public class ArenaShooter : ModuleRules
{
	public ArenaShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"GameplayTasks",
			"PhysicsCore",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"ArenaShooter/Public/Player", 
			"ArenaShooter/Public/Components",
			"ArenaShooter/Public/Dev",
			"ArenaShooter/Public/Weapon",
			"ArenaShooter/Public/Components",
			"ArenaShooter/Public/UI",
			"ArenaShooter/Public/Animations",
			"ArenaShooter/Public/PickUps",
			"ArenaShooter/Public/AI",
			"ArenaShooter/Public/AI/Tasks",
			"ArenaShooter/Public/AI/Services",
			"ArenaShooter/Public/AI/EQS",
			"ArenaShooter/Public/AI/Decorators",
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
