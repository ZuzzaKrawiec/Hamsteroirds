// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlooberTeam : ModuleRules
{
	public BlooberTeam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
            "Slate", 
            "SlateCore", 
            "UMG", 
            "RenderCore", 
            "Paper2D", 
            "CableComponent",
            "EnhancedInput"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { "CableComponent", "EnhancedInput" });

        PublicIncludePaths.AddRange(new string[]
        {
            ModuleDirectory
        });
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
