#!/bin/bash

MYDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
GIT_CHECKOUT_DIR="${MYDIR}/.."

echo $MYDIR
echo $GIT_CHECKOUT_DIR

# brew
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

# git setup
## git-lfs
brew install git-lfs
git lfs install

## git basic config
git config --global color.ui true
git config --global core.editor nano

## check if need to clone
if [ -d "${GIT_CHECKOUT_DIR}/.git" ]; then
    echo "Repo already cloned"
else
    git clone --recursive https://github.com/remap/GrasshopperAR
    GIT_CHECKOUT_DIR="`pwd`/GrasshopperAR"
    MYDIR="${GIT_CHECKOUT_DIR}/scripts"
fi;

cd "${GIT_CHECKOUT_DIR}"

## create a branch
username=`git config user.name`
userbranch="`echo ${username% *} | awk '{print tolower($0)}'`-dev"
git checkout -b $userbranch

# setup unreal project
## generate project files
. "${MYDIR}/helper.sh"

"${MYDIR}/build.sh" --project
if [ $? -ne 0 ]; then
    showPopup "Project build failed"
else
    showPopup "Project build succeeded"
    open "${GIT_CHECKOUT_DIR}/GrasshopperAR.uproject"
fi
