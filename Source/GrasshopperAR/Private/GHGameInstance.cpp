// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameInstance.h"
#include "DDLog.h"
#include "DDBlueprintLibrary.h"
#include "git-describe.h"

#include <Misc/NetworkVersion.h>

#include <string>
#include <sstream>

using namespace std;

#define BRANCH_NAME_MASTER "master"
#define BRANCH_NAME_DEVELOPMENT "dev"
#define BRANCH_NAME_STAGE "stage"

#define STRINGIZE_VERSION(v) STRINGIZE_TOKEN(v)
#define STRINGIZE_TOKEN(t) #t
#define CODE_VERSION STRINGIZE_VERSION(GIT_DESCRIBE)
#define BRANCH_NAME STRINGIZE_VERSION(GIT_BRANCH)
#define CODE_COMMIT STRINGIZE_VERSION(GIT_COMMIT)

UGHGameInstance::UGHGameInstance()
:UGameInstance()
{
    // this constructor is not called.
    DLOG_DEBUG("GAME INSTANCE DEFAULT CTOR");
}

UGHGameInstance::UGHGameInstance(const FObjectInitializer& ObjectInitializer)
:UGameInstance(ObjectInitializer)
{
    setNetworkVersionOverride();
    
    DLOG_DEBUG("GAME INSTANCE CTOR");
    DLOG_INFO("Game Instance Network Version {}",
              TCHAR_TO_ANSI(*UDDBlueprintLibrary::getNetworkVersion()));
}

UGHGameInstance::~UGHGameInstance()
{
    DLOG_DEBUG("GAME INSTANCE DTOR");
}

FString
UGHGameInstance::getCodeVersion() const
{
    return FString(CODE_VERSION);
}

FString
UGHGameInstance::getBranchName() const
{
    return FString(BRANCH_NAME);
}

void
UGHGameInstance::setNetworkVersionOverride()
{
    FNetworkVersion::GetLocalNetworkVersionOverride.BindStatic( &UGHGameInstance::getNetworkVersionGrasshopper);
}

uint32
UGHGameInstance::getNetworkVersionGrasshopper()
{
    string codeVersion(CODE_COMMIT);
    string branchName(BRANCH_NAME);
    
    unsigned int networkVersion = 0;
    {
        size_t p = codeVersion.find("-dirty");
    
        if (p != string::npos)
            codeVersion = codeVersion.substr(0, p);
    
        DLOG_TRACE("Commit hash string {}", codeVersion);
        
        stringstream ss;
        ss << hex << codeVersion;
        unsigned int commitHash;
        ss >> commitHash;
        
        DLOG_TRACE("Commit hash (decimal) {}", commitHash);
        
        networkVersion += commitHash;
    }
    
    // alter networkVersionn for different app branches
    if (branchName == BRANCH_NAME_DEVELOPMENT)
    {
        networkVersion += 2;
    }
    else if (branchName == BRANCH_NAME_STAGE)
    {
        networkVersion += 1;
    }
    
    DLOG_DEBUG("Override NetworkVersion {}", networkVersion);
    
    return networkVersion;
}
