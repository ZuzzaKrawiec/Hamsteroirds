// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlooberTeamEditor : ModuleRules
{
	public BlooberTeamEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "PropertyEditor", 
            "UnrealEd",
            "Slate", 
            "SlateCore", 
            "UMG",
            "BlooberTeam"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.AddRange(new string[]
        {
            ModuleDirectory
        });
    }
}
