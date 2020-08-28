# GrasshopperAR
UE4 Shell App for Grasshopper AR project.

## Environment Setup

### Prerequisites

1. [Unreal Engine 4.25.3](https://www.unrealengine.com/en-US/get-now)
2. Dev tools:
    * **macOS** [Xcode](https://apps.apple.com/us/app/xcode/id497799835?mt=12)
	    * Install Xcode using AppStore
	    * Open Xcode and Agree to the license
	    * Install additional developer tools when prompted
	    * Close Xcode
    * **win** [Visual Studio 2019](https://visualstudio.microsoft.com/vs/)
3. [GitHub](http://github.com/) account
    * Make sure your account is added to REMAP organization (let us know).
4. [GitHub Desktop Client](https://desktop.github.com/)
	* Open GitHub Desktop Client after installing
	* Authenticate with your GitHub account you created in step 3

### Bootstrapping

#### macOS

Open Terminal.app, copy and paste command below and hit Enter:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/remap/GrasshopperAR/master/scripts/bootstrap.sh)"
```

Enter your laptop password to authorize installation and press ENTER whenever scripts asks you.

#### win

1. Open GitHub Desktop Client
	* Authenticate with your GitHub account if you haven't done it yet
2. Click on the menu carrot beside *Current Repository* and select *Add -> Clone Repository*
3. Enter the url of the project: https://github.com/remap/GrasshopperAR
	* Under *Local Path* select the folder in which you’d like the repo to save.
	* Wait for the clone to complete.
	* Initialize Git-LFS when prompted.
4. Press `Ctrl + Shift + F`
5. Double-click on `_BOOTSTRAP_WIN.bat`

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
