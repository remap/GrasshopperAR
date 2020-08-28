# GrasshopperAR
UE4 Shell App for Grasshopper AR project.

## Environment Setup

### Prerequisites



### Bootstrapping

::macOS::

Open Terminal.app, copy and paste command below and hit Enter:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/remap/GrasshopperAR/master/scripts/bootstrap.sh)"
```

Enter your laptop password to authorize installation and Press Enter whenever scripts asks you.

## Description

TBD

## Project folder structure

```
.
├── Config    // configuration files for multiplatform build
├── Content   // ShellApp content goes here
│   ├── Blueprints
│   │   ├── BP_ARController.uasset   // AR Player Controller
│   │   ├── BP_ARGameMode.uasset     // AR Game Mode
│   │   ├── BP_ARPawn.uasset         // AR Pawn
│   │   ├── BP_VRController.uasset   // VR Player Controller
│   │   ├── BP_VRGameMode.uasset     // VR Game Mode
│   │   ├── BP_VRPawn.uasset         // VR Pawn
│   │   └── UI
│   │       ├── BP_DebugMenu.uasset
│   │       ├── WD_PluginButton.uasset
│   │       └── BP_Master.uasset     // Master UI
│   ├── Data
│   │   └── D_SessionConfig.uasset   // AR Session Config file
│   └── Maps
│       ├── M_ARLevel0.umap   // AR Level Map
│       └── M_VRLevel0.umap   // VR Level Map
├── Plugins
│   ├── ...       // ALL DEV GROUPS PLUGINS ARE HERE
│   └── DDTools   // DDTools plugin (development tools)
├── Source        // ShellApp source code. SHOULD NOT BE TOUCHED
│   ├── GrasshopperAR
│   │   ├── GrasshopperAR.Build.cs
│   │   ├── GrasshopperAR.cpp
│   │   ├── GrasshopperAR.h
│   │   ├── GrasshopperARGameModeBase.cpp
│   │   └── GrasshopperARGameModeBase.h
│   ├── GrasshopperAR.Target.cs
│   └── GrasshopperAREditor.Target.cs
└── GrasshopperAR.uproject
```
