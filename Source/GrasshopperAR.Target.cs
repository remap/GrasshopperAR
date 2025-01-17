// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GrasshopperARTarget : TargetRules
{
	public GrasshopperARTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        
		ExtraModuleNames.AddRange( new string[] { "GrasshopperAR", "DDHelpers", "DDManager", "DDBase", "DDLog", "DDBlueprints" } );
        
        if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            bOverrideBuildEnvironment = true;
            GlobalDefinitions.Add("FORCE_ANSI_ALLOCATOR=1");
        }
	}
}
