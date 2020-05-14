// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class GrasshopperARServerTarget : TargetRules   // Change this line as shown previously
{
       public GrasshopperARServerTarget(TargetInfo Target) : base(Target)  // Change this line as shown previously
       {
        Type = TargetType.Server;
        bUsesSteam = false;
        ExtraModuleNames.Add("GrasshopperAR");    // Change this line as shown previously
       }
}