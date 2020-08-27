#!/bin/bash
MYDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
UEDIR="/Users/Shared/Epic Games/UE_4.25"
CMD_GEN_PROJECT="$UEDIR/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh"
CMD_RUN_UAT="$UEDIR/Engine/Build/BatchFiles/RunUAT.sh"
CMD_UE_EDITOR="$UEDIR/Engine/Binaries/Mac/UE4Editor-Cmd"

"$CMD_GEN_PROJECT" -project="${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject" -game
xcodebuild -scheme GrasshopperAR build

"$CMD_RUN_UAT" BuildCookRun \
-nocompileeditor -nop4 \
-project="${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject" \
-cook -stage -archive \
-archivedirectory="${GIT_CHECKOUT_DIR}/Packaged" \
-package -clientconfig=Shipping \
-ue4exe="$CMD_UE_EDITOR" \
-clean -pak -prereqs -nodebuginfo -targetplatform=Mac -build -utf8output -compile
