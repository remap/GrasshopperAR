#!/bin/bash
MYDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
GIT_CHECKOUT_DIR="${MYDIR}/.."
UEDIR="/Users/Shared/Epic Games/UE_4.25"

function goToRepo()
{
    cd "${GIT_CHECKOUT_DIR}"
}

function buildProject()
{
    CMD_GEN_PROJECT="$UEDIR/Engine/Build/BatchFiles/Mac/GenerateProjectFiles.sh"

    goToRepo

    echo "Generating project files..."
    "$CMD_GEN_PROJECT" -project="${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject" -game

    echo "Building project using Xcode..."
    xcodebuild -scheme GrasshopperAR build
}


function buildLighting()
{
    CMD_UE_EDITOR="$UEDIR/Engine/Binaries/Mac/UE4Editor-Cmd"
    # "$CMD_UE_EDITOR" "${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject" \
    # -run=resavepackages -buildlighting -quality=High -allowcommandletrendering

    CMD_RUN_UAT="$UEDIR/Engine/Build/BatchFiles/RunUAT.sh"

    echo "Building lighting..."
    "$CMD_RUN_UAT" RebuildLightmaps \
    -project="${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject" -allmaps
}

function packageProject()
{
    CMD_RUN_UAT="$UEDIR/Engine/Build/BatchFiles/RunUAT.sh"
    CMD_UE_EDITOR="$UEDIR/Engine/Binaries/Mac/UE4Editor-Cmd"

    buildProject
    goToRepo

    case "$1" in
        ios)
            platform="IOS -distribution"
            ;;
        *)
            platform="Mac"
            ;;
    esac

    echo "Packaging project into ${GIT_CHECKOUT_DIR}/Packaged ..."
    "$CMD_RUN_UAT" BuildCookRun \
    -nocompileeditor -nop4 \
    -project="${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject" \
    -cook -stage -archive \
    -archivedirectory="${GIT_CHECKOUT_DIR}/Packaged" \
    -package -clientconfig=Shipping \
    -ue4exe="$CMD_UE_EDITOR" \
    -clean -pak -prereqs -nodebuginfo -targetplatform=$platform -build -utf8output
}

arg="$1"
case $arg in
    --project)
        buildProject
        ;;
    --package)
        packageProject "mac"
        ;;
    --packageios)
        packageProject "ios"
        ;;
    --lighting)
        buildLighting
        ;;
    *)
        echo "build.sh [ project | package ]"
        exit 1;;
esac
