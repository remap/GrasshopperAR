// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameInstance.h"
#include "DDLog.h"
#include "DDBlueprintLibrary.h"
#include "DDManager.h"
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
    connectionStatus_ = Disconnected;
    
    // this constructor is not called.
    DLOG_DEBUG("GAME INSTANCE DEFAULT CTOR");
}

UGHGameInstance::UGHGameInstance(const FObjectInitializer& ObjectInitializer)
:UGameInstance(ObjectInitializer)
{
    connectionStatus_ = Disconnected;
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

ConnectionStatus
UGHGameInstance::getConnectionStatus() const
{
    return connectionStatus_;
}

void
UGHGameInstance::setConnectionStatus(ConnectionStatus status)
{
    connectionStatus_ = status;
}

bool
UGHGameInstance::HandleOpenCommand(const TCHAR * Cmd, FOutputDevice & Ar, UWorld * InWorld)
{
    DLOG_TRACE("Open level command received");
    
    if (Cmd)
        DLOG_TRACE("Cmd: {}", TCHAR_TO_ANSI(Cmd));

    if (InWorld)
        DLOG_TRACE("World: {}", TCHAR_TO_ANSI(*InWorld->GetMapName()));
    
    updateConnectionStatus(Connecting);
    
    return UGameInstance::HandleOpenCommand(Cmd, Ar, InWorld);
}

void
UGHGameInstance::LoadComplete(const float LoadTime, const FString & MapName)
{
    DLOG_TRACE("LoadComplete: time {} map name {}",
               LoadTime, TCHAR_TO_ANSI(*MapName));
    UWorld *world = FDDModuleManager::getSharedInstance()->getLastWorldCreated();
    
    // check if we really connected
    if (world)
    {
        ENetMode mode = world->GetNetMode();
        switch (mode) {
            case NM_Standalone:
                updateConnectionStatus(Disconnected);
                DLOG_TRACE("Client is not connected");
                break;
            case NM_Client:
                updateConnectionStatus(Connected);
                DLOG_TRACE("Client has connected to a server");
                break;
            case NM_ListenServer:
                updateConnectionStatus(Connected);
                DLOG_TRACE("Client is a listen server");
                break;
            case NM_DedicatedServer:
                updateConnectionStatus(Connected);
                DLOG_TRACE("Client is a dedicated server");
                break;
            default:
                // do nothing
                break;
        }
    }
}


void
UGHGameInstance::notifyPlayerStateUpdate(bool oldIsActive, bool newIsActive)
{
    OnPlayerStateUpdated.Broadcast(oldIsActive, newIsActive);
}

void
UGHGameInstance::updateConnectionStatus(ConnectionStatus newStatus)
{
    if (connectionStatus_ != newStatus)
    {
        ConnectionStatus oldStatus = connectionStatus_;
        connectionStatus_ = newStatus;
        
        // notify observers
        OnConnectionStatusUpdated.Broadcast(oldStatus, connectionStatus_);
    }
}
